#include "minishell.h"

int	mvs_open(char *file, int mode)
{
	int	fd;

	if (mode == READ)
		fd = open(file, O_RDONLY, 0777);
	else if (mode == WRITE)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

int	here_doc(int infile, char *limiter)
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
	if (infile == -1)
		return (FAILURE);
	return (SUCCESS);
}
