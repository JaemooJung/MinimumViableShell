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

static char	*make_path(char *cmd, char *path)
{
	char	*temp;

	temp = ft_strjoin("/", cmd);
	if (temp == NULL)
		return (NULL);
	path = ft_strjoin(path, temp);
	if (path == NULL)
	{
		ft_free_str(temp);
		return (NULL);
	}
	ft_free_str(temp);
	return (path);
}

static int	concat_path(char **cmd, t_list *env, int i)
{
	char	**paths;
	char	*path;

	paths = ft_split(get_value(env, "PATH") + 5, ':');
	if (paths == NULL)
		return (FAILURE);
	while (paths[i] != NULL)
	{
		path = make_path(*cmd, paths[i++]);
		if (path == NULL)
			return (FAILURE);
		if (open_for_check(path) == SUCCESS)
		{
			ft_free_vector(paths);
			ft_free_str(*cmd);
			*cmd = path;
			return (SUCCESS);
		}
		ft_free_str(path);
	}
	ft_free_vector(paths);
	return (127);
}

int	get_fullpath(char **content, t_info *info)
{
	int	stat;

	if (classify_builtin(*content) != NONE)
		return (SUCCESS);
	stat = concat_path(content, info->env, 0);
	if (stat == SUCCESS)
		info->fullpath = *content;
	else if (stat == FAILURE)
		ft_print_error(NULL, NULL, strerror(errno));
	else if (stat == 127)
	{
		if (open_for_check(*content) == SUCCESS)
		{
			info->fullpath = *content;
			stat = SUCCESS;
		}
		else
			ft_print_error("command not found", NULL, *content);
	}
	return (stat);
}
