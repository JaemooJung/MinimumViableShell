#include "minishell.h"

int	teach_me_direction(char *content, t_info *info)
{
	if (ft_strncmp(content, "<", 2) == 0)
		info->prev_dir = IN_REDIR;
	else if (ft_strncmp(content, "<<", 3) == 0)
		info->prev_dir = IN_HEREDOC;
	else if (ft_strncmp(content, ">", 2) == 0)
		info->prev_dir = OUT_REDIR;
	else if (ft_strncmp(content, ">>", 3) == 0)
		info->prev_dir = OUT_APPEND;
	else
		return (FAILURE);
	return (SUCCESS);
}

static int	input_redir(char *content, t_info *info)
{
	if (info->prev_dir == IN_REDIR)
	{
		info->fd[INFILE] = mvs_open(content, READ);
		if (info->fd[INFILE] == -1)
			return (ft_print_error(NULL, content, strerror(errno)));
		if (dup2(info->fd[INFILE], STDIN_FILENO) == -1)
			return (ft_print_error("Dup didn't work!", NULL, NULL));
	}
	else if (info->prev_dir == IN_HEREDOC)
	{
		if (dup2(info->origin[0], STDIN_FILENO) == -1)
			return (ft_print_error("Dup didn't work!", NULL, NULL));
		info->fd[INFILE] = mvs_open("mvs_temp", WRITE);
		here_doc(info->fd[INFILE], content);
		if (info->fd[INFILE] == -1)
			return (ft_print_error(NULL, content, strerror(errno)));
		if (dup2(info->fd[INFILE], STDIN_FILENO) == -1)
			return (ft_print_error("Dup didn't work!", NULL, NULL));
	}
	return (SUCCESS);
}

static int	output_redir(char *content, t_info *info)
{
	if (info->prev_dir == OUT_REDIR)
	{
		info->fd[OUTFILE] = mvs_open(content, WRITE);
		if (info->fd[OUTFILE] == -1)
			return (ft_print_error(NULL, content, strerror(errno)));
		if (dup2(info->fd[OUTFILE], STDOUT_FILENO) == -1)
			return (ft_print_error("Dup didn't work!", NULL, NULL));
	}
	else if (info->prev_dir == OUT_APPEND)
	{
		info->fd[OUTFILE] = mvs_open(content, APPEND);
		if (info->fd[OUTFILE] == -1)
			return (ft_print_error(NULL, content, strerror(errno)));
		if (dup2(info->fd[OUTFILE], STDOUT_FILENO) == -1)
			return (ft_print_error("Dup didn't work!", NULL, NULL));
	}
	return (SUCCESS);
}

int	redir_n_join_remainder(t_list *content, t_info *info)
{
	int	fd;

	if (ft_lstsize(content) > 1)
	{
		ft_lstadd_back(&info->remainder, content->next);
		content->next = NULL;
	}
	if (info->prev_dir == IN_REDIR || info->prev_dir == IN_HEREDOC)
	{
		if (input_redir(content->line, info) == FAILURE)
			return (FAILURE);
	}
	else if (info->prev_dir == OUT_REDIR || info->prev_dir == OUT_APPEND)
	{
		if (output_redir(content->line, info) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
