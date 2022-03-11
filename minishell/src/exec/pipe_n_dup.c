#include "minishell.h"

int	keep_stdio(int *origin)
{
	origin[0] = dup(STDIN_FILENO);
	if (origin[0] == -1)
		return (FAILURE);
	origin[1] = dup(STDOUT_FILENO);
	if (origin[0] == -1)
		return (FAILURE);
	return (SUCCESS);
}

int	restore_stdio(int *origin)
{
	if (dup2(origin[0], STDIN_FILENO) == -1)
		return (FAILURE);
	if (dup2(origin[1], STDOUT_FILENO) == -1)
		return (FAILURE);
	return (SUCCESS);
}

int	lets_pipe(t_info *info)
{
	if (pipe(info->pipe) == -1)
		return (FAILURE);
	info->pipeexists = true;
	return (SUCCESS);
}
