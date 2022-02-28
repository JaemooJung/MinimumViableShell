#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>

# define SPACE ' '
# define SQUOTE '\''
# define DQUOTE '\"'

bool	m_is_space(char c);
bool	m_is_quote(char c);
void	ft_free_split(char **splitted, int index);
char	**mvs_split(char const *s);

#endif