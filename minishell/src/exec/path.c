#include "minishell.h"

int	open_for_check(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	close(fd);
	if (fd >= 0)
		return (SUCCESS);
	else
		return (FAILURE);
}

int	concat_path(char **cmd, t_list *env, int i)
{
	char	**paths;
	char	*path;
	char	*temp;

	paths = ft_split(get_value(env, "PATH") + 5, ':');
	if (paths == NULL)
		return (FAILURE);
	while (paths[i] != NULL)
	{
		temp = ft_strjoin("/", *cmd);
		if (temp == NULL)
			return (FAILURE);
		path = ft_strjoin(paths[i++], temp);
		if (path == NULL)
			return (FAILURE);
		ft_free_str(temp);
		if (open_for_check(path) == SUCCESS)
		{
			ft_free_str(*cmd);
			*cmd = path;
			return (SUCCESS);
		}
		ft_free_str(path);
	}
	return (FAILURE);
}

int	get_fullpath(char *content, t_info *info)
{
	int	stat;

	if (ft_strncmp(content, "cd", 3) == 0
		|| ft_strncmp(content, "echo", 5) == 0
		|| ft_strncmp(content, "env", 5) == 0
		|| ft_strncmp(content, "exit", 5) == 0
		|| ft_strncmp(content, "export", 5) == 0
		|| ft_strncmp(content, "pwd", 5) == 0
		|| ft_strncmp(content, "unset", 5) == 0)
		return (SUCCESS);
	info->binary = content;
	stat = concat_path(&content, info->env, 0);
	if (stat == SUCCESS)
		info->fullpath = content;
	else if (stat == FAILURE)
		ft_print_error("command not found", NULL, info->binary);
	return (stat);
}
