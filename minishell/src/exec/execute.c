#include "minishell.h"

static int	do_child_proc(char **cmd_splitted, t_info *info, char **chunk)
{
	char	**envp;
	int		builtin;
	int		(*builtins[8])(char **, t_list *);

	envp = to_vector(info->env);
	if (envp == NULL)
		exit(EXIT_FAILURE);
	if (info->pipeexists)
	{
		close(info->pipe[0]);
		if (dup2(info->pipe[1], STDOUT_FILENO) == -1)
			return (ft_print_error("Dup didn't work!", NULL, NULL));
	}
	builtins_init(builtins);
	builtin = classify_builtin(chunk[0]);
	if (builtin != NONE)
		exit(builtins[builtin](chunk, info->env));
	execve(info->fullpath, cmd_splitted, envp);
	if (execve(cmd_splitted[0], cmd_splitted, envp) == -1)
		exit(126 + ft_print_error("command not found", NULL, cmd_splitted[0]));
	return (SUCCESS);
}

static int	do_parent_proc(char *cmd, pid_t pid, t_info *info)
{
	int	status;

	if (info->pipeexists)
	{
		close(info->pipe[1]);
		if (dup2(info->pipe[0], STDIN_FILENO) == -1)
			return (ft_print_error("Dup didn't work!", NULL, NULL));
	}
	if ((ft_strlen(cmd) == ft_strlen("./minishell"))
		&& ft_strncmp(cmd, "./minishell", 11) == 0)
		signal_waiting_for_new_shell();
	waitpid(pid, &status, 0);
	signal_handler_init();
	if (info->pipeexists)
		close(info->pipe[0]);
	info->exit_status = WEXITSTATUS(status);
	return (SUCCESS);
}

static int	lets_exec(char *cmd, t_info *info, char **chunk)
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
		return (ft_print_error("You've got broken fork...", NULL, NULL));
	if (pid == 0)
		do_child_proc(cmd_splitted, info, chunk);
	do_parent_proc(cmd_splitted[0], pid, info);
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
	chunk = mvs_split(cmd);
	if (chunk == NULL)
	{
		ft_free_str(cmd);
		return (FAILURE);
	}
	builtins_init(builtins);
	builtin = classify_builtin(chunk[0]);
	if (builtin != NONE && info->wasthereanypipe == false)
		stat = builtins[builtin](chunk, info->env);
	else
		stat = lets_exec(cmd, info, chunk);
	info->pipeexists = false;
	ft_free_str(cmd);
	ft_free_vector(chunk);
	return (stat);
}
