#include "minishell.h"

void	keep_stdio(int *origin) // dup errorhandling
{
	origin[0] = dup(STDIN_FILENO);
	origin[1] = dup(STDOUT_FILENO);
}

void restore_stdio(int *origin) // dup errorhandling
{
	dup2(origin[0], STDIN_FILENO);
	dup2(origin[1], STDOUT_FILENO);
}
/*//argument should include if there is a pipe in mother, original fdarr,
void	run_token(t_list *env) // yesfork
{
	char	**envv;
	int		pipe[2];
	pid_t	pid;

	envv = to_vector(env);
	if (envv == NULL)
		; //dosomething
	// check if there is pipe
//	if (i have to do pipe)
//		if (pipe(pipe) == -1)
//			err!!
	pid = fork();
//	if (pid == -1)
//		err!
	if (pid == 0) // child
	{
//		child_redirection -> STDIN // STDOUT redirect
//		execve(filepath, argv, envv);
	}
	else // mother
	{
//		mom_redirection
		waitpid(pid, 0, 0);
	}
//	free_vector(envv);
//	fd_restore();
}*/

t_stat	here_doc(int infile, char *limiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			ft_free_str(line);
			break ;
		}
		write(infile, line, ft_strlen(line));
		ft_free_str(line);
	}
	close(infile);
	infile = open("mvs_temp", O_RDONLY, 0777);
	if (infile == NULL)
		return (MALLOC_ERR);
	return (SUCCESS);
}

t_stat	lets_pipe(t_info *info)
{
	if (pipe(info->pipe) == -1)
		return (MALLOC_ERR);
	info->pipeexists = true;
	return (SUCCESS);
}

t_stat	teach_me_direction(char *content, t_info *info)
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
		return (MALLOC_ERR);
	return (SUCCESS);
}

t_stat	join_remainder(char *content, t_info *info)
{
	int 	space_loc;
	char	*temp;

	space_loc = 0;
	while (content[space_loc] != ' ')
		++space_loc;
	temp = info->remainder;
	info->remainder = ft_strjoin(info->remainder, &content[space_loc + 1]);
	if (temp != NULL)
		return (ft_free_str(temp));
	content[space_loc] = '\0';
	return (SUCCESS);
}

int	mvs_open(char *file, int mode)
{
	int	fd;

	if (mode == READ)
		fd = open(file, O_RDONLY, 0777);
	else if (mode == WRITE)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	return (fd);
}

void	redir_n_join_remainder(char *content, t_info *info)
{
	int 	fd;

	if (ft_strchr(content, ' ') != NULL)
		join_remainder(content, info);
	if (info->prev_dir == IN_REDIR)
	{
		info->fd[INFILE] = mvs_open(content, READ);
		dup2(info->fd[INFILE], STDIN_FILENO);
	}
	else if (info->prev_dir == IN_HEREDOC)
	{
		info->fd[INFILE] = mvs_open("mvs_temp", WRITE);
		here_doc(info->fd[INFILE], content);
		dup2(info->fd[INFILE], STDIN_FILENO);
	}
	else if (info->prev_dir == OUT_REDIR)
	{
		info->fd[OUTFILE] = mvs_open(content, WRITE);
		dup2(info->fd[OUTFILE], STDOUT_FILENO);
	}
	else if (info->prev_dir == OUT_APPEND)
	{
		info->fd[OUTFILE] = mvs_open(content, APPEND);
		dup2(info->fd[OUTFILE], STDOUT_FILENO);
	}
}

char	*concat_path(char *cmd, t_list *env)
{
	char	**paths;
	char	*path;
	char	*temp;
	int		i;

	paths = ft_split(get_value(env, "PATH") + 5, ':');
	if (paths == 0)
		return (MALLOC_ERR);
	i = 0;
	while (paths[i] != 0)
	{
		temp = ft_strjoin("/", cmd);
		path = ft_strjoin(paths[i], temp);
		if (temp == NULL || path == NULL)
			return (MALLOC_ERR);
		free(temp);
		if (access(path, X_OK) == 0) // access is not allowed!
			return (path);
		++i;
		ft_free_str(path);
	}
	return (0);
}

void	get_fullpath(char *content, t_info *info)
{
	/* have to filter builtins */
	info->fullpath = concat_path(content, info->env);
//	if (info->fullpath == 0)
//		error(ERR);
}

void	lets_exec(char *content, t_info *info)
{
	char	**cmd_splitted;
	char	**envp;
	char 	*temp;
	pid_t	pid;

	temp = content;
	envp = to_vector(info->env);
	content = ft_strjoin(content, info->remainder);
//	if (content == NULL)
//		;
	cmd_splitted = mvs_split(content);
	if (info->fullpath == NULL)
		return ;
	pid = fork();
	if (pid == 0)
	{
		if (info->pipeexists)
		{
			close(info->pipe[0]);
			dup2(info->pipe[1], STDOUT_FILENO);
		}
		if (execve(info->fullpath, cmd_splitted, envp) == -1)
			;
//		error(ERR);
	}
	if (info->pipeexists)
	{
		close(info->pipe[1]);
		dup2(info->pipe[0], STDIN_FILENO);
		close(info->pipe[0]);
	}
	waitpid(pid, NULL, WUNTRACED);
	ft_free_str(info->remainder);
	//have to free cmd_splitted
	/* strjoin info->remainder and free. then split */
	/* have to clear info->remainder in parent proc */
}

void	builtin_or_not(char *content, t_info *info)
{
	char **chunk;

	chunk = mvs_split(content);
	if (ft_strncmp(content, "cd", 3) == 0)
		mvs_cd(chunk, info->env);
	else if (ft_strncmp(content, "echo", 5) == 0)
		mvs_echo(chunk, info->env);
	else if (ft_strncmp(content, "env", 5) == 0)
		mvs_env(chunk, info->env);
	else if (ft_strncmp(content, "exit", 5) == 0)
		mvs_exit(chunk, info->env);
	else if (ft_strncmp(content, "export", 5) == 0)
		mvs_export(chunk, info->env);
	else if (ft_strncmp(content, "pwd", 5) == 0)
		mvs_pwd(chunk, info->env);
	else if (ft_strncmp(content, "unset", 5) == 0)
		mvs_unset(chunk, info->env);
	else
		lets_exec(content, info);
}


/* have to handle errors for ftstrjoins.... */
/* in the function that use search_tree,
 * we need to use keep_stdio and restore_stdio*/
void	execute_tree(t_ast_node *node, t_info *info)
{
	if (node->node_type == NODE_PIPE && node->right != NULL)
		lets_pipe(info);
//	else if (node->node_type == NODE_PHRASE)
//		do_nothing();
//	else if (node->node_type == NODE_REDIRS)
//		do_nothing();
//	else if (node->node_type == NODE_IO_REDIR)
//		do_nothing();
//	else if (node->node_type == NODE_COMMAND)
//		do_nothing();
	else if (node->node_type == NODE_REDIR_TYPE)
		teach_me_direction(node->content, info);
	else if (node->node_type == NODE_FILE_NAME)
		redir_n_join_remainder(node->content, info);
	else if (node->node_type == NODE_FILE_PATH)
		get_fullpath(node->content, info);
	else if (node->node_type == NODE_ARGV)
		builtin_or_not(node->content, info);
}

void search_tree(t_ast_node *node, t_info *info)
{
	execute_tree(node, info);
	if (node->left != NULL)
		search_tree(node->left, info);
	if (node->right != NULL)
		search_tree(node->right, info);
}

void run_tokens(t_ast_node *node, t_list *env)
{
	int origin[2];
	t_info info;

	info.env = env;
	info.pipeexists = false;
	info.remainder = NULL;
	keep_stdio(origin);
	search_tree(node, &info);
	restore_stdio(origin);
	// if heredoc was used, have to unlink temp file
}