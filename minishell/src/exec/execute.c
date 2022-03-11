#include "minishell.h"

static int	do_child_proc(char **cmd_splitted, char **envp, t_info *info)
{
	if (info->pipeexists)
	{
		close(info->pipe[0]);
		if (dup2(info->pipe[1], STDOUT_FILENO) == -1)
			return (FAILURE);
	}
	if (execve(info->fullpath, cmd_splitted, envp) == -1)
		return (FAILURE);
	return (SUCCESS);
}

static int	do_parent_proc(pid_t pid, t_info *info)
{
	if (info->pipeexists)
	{
		close(info->pipe[1]);
		if (dup2(info->pipe[0], STDIN_FILENO) == -1)
			return (FAILURE);
		close(info->pipe[0]);
	}
	waitpid(pid, NULL, WUNTRACED);
	return (SUCCESS);
}

static int	lets_exec(char *content, t_info *info)
{
	char	**cmd_splitted;
	char	**envp;
	pid_t	pid;

	envp = to_vector(info->env);
	if (envp == NULL)
		return (FAILURE);
	content = ft_strjoin(content, info->remainder);
	if (content == NULL)
		return (FAILURE);
	cmd_splitted = mvs_split(content);
	if (cmd_splitted == NULL)
		return (FAILURE);
	if (info->fullpath == NULL)
		return (FAILURE);
	pid = fork();
	if (pid == -1)
		return (FAILURE);
	if (pid == 0)
		do_child_proc(cmd_splitted, envp, info);
	do_parent_proc(pid, info);
	ft_free_str(content);
	ft_free_vector(envp);
	ft_free_vector(cmd_splitted);
	return (SUCCESS);
}

int	builtin_or_not(char *content, t_info *info)
{
	char	**chunk;
	int		stat;

	chunk = mvs_split(content);
	if (ft_strncmp(content, "cd", 3) == 0)
		stat = mvs_cd(chunk, info->env);
	else if (ft_strncmp(content, "echo", 5) == 0)
		stat = mvs_echo(chunk, info->env);
	else if (ft_strncmp(content, "env", 5) == 0)
		stat = mvs_env(chunk, info->env);
	else if (ft_strncmp(content, "exit", 5) == 0)
		stat = mvs_exit(chunk, info->env);
	else if (ft_strncmp(content, "export", 5) == 0)
		stat = mvs_export(chunk, info->env);
	else if (ft_strncmp(content, "pwd", 5) == 0)
		stat = mvs_pwd(chunk, info->env);
	else if (ft_strncmp(content, "unset", 5) == 0)
		stat = mvs_unset(chunk, info->env);
	else
		stat = lets_exec(content, info);
	return (stat);
}
