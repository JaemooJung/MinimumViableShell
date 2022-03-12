#include "minishell.h"

static void	do_child_proc(char **cmd_splitted, t_info *info)
{
	char	**envp;

	envp = to_vector(info->env);
	if (envp == NULL)
		exit(EXIT_FAILURE);
	if (info->pipeexists)
	{
		close(info->pipe[0]);
		dup2(info->pipe[1], STDOUT_FILENO);
	}
	execve(info->fullpath, cmd_splitted, envp);
}

static int	do_parent_proc(pid_t pid, t_info *info)
{
	int	status;

	if (info->pipeexists)
	{
		close(info->pipe[1]);
		if (dup2(info->pipe[0], STDIN_FILENO) == -1)
			return (FAILURE);
		close(info->pipe[0]);
	}
	waitpid(pid, &status, 0);
	info->exit_status = WEXITSTATUS(status);
	return (SUCCESS);
}

static int	lets_exec(char *cmd, t_info *info)
{
	char	**cmd_splitted;
	pid_t	pid;

	cmd_splitted = mvs_split(cmd);
	if (cmd_splitted == NULL)
		return (FAILURE);
	if (info->fullpath == NULL)
		return (FAILURE);
	pid = fork();
	if (pid == -1)
		return (FAILURE);
	if (pid == 0)
		do_child_proc(cmd_splitted, info);
	do_parent_proc(pid, info);
	ft_free_vector(cmd_splitted);
	return (info->exit_status);
}

int	builtin_or_not(char *content, t_info *info)
{
	char	**chunk;
	char	*cmd;
	int		stat;
	int		builtin;
	int		(*builtins[8])(char **, t_list *);

	cmd = ft_strjoin(content, info->remainder);
	if (cmd == NULL)
		return (FAILURE);
	chunk = mvs_split(content);
	if (chunk == NULL)
	{
		ft_free_str(cmd);
		return (FAILURE);
	}
	builtins_init(builtins);
	builtin = classify_builtin(chunk[0]);
	if (builtin != NONE)
		stat = builtins[builtin](chunk, info->env);
	else
		stat = lets_exec(content, info);
	ft_free_str(cmd);
	ft_free_vector(chunk);
	return (stat);
}