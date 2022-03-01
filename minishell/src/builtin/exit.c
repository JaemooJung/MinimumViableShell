/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:34:14 by hakim             #+#    #+#             */
/*   Updated: 2022/03/01 14:34:22 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minilibft.c"

static bool is_white_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

static bool	can_be_atoied(char *str)
{
	int	i;

	i = 0;
	while (is_white_space(str[i]) == true)
		++i;
	while (str[i] != '\0' && is_white_space(str[i]) == false)
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (false);
		++i;
	}
	while (is_white_space(str[i]) == true && str[i] != '\0')
		++i;
	if (str[i] == '\0')
		return (true);
	return (false);
}

void	dequote(char *str)
{
	int	i;

	if (!(str[0] == '\"' && str[ft_strlen(str) - 1] == '\"'))
		return ;
	i = 1;
	while (i < ft_strlen(str) - 1)
	{
		str[i - 1] = str[i];
		++i;
	}
	str[i] = '\0';
}

void	mvs_exit(char **chunk)
{
	int 	i;

	i = 0;
	while (chunk[i] != NULL)
		i++;
	if (i == 1)
		exit(EXIT_SUCCESS);
	if (i > 2)
		return (ft_putstr_fd("mvshell: exit: too many arguments", 2));
	dequote(chunk[1]);
	printf("%s\n", chunk[1]);
	if (can_be_atoied(chunk[1]) == false)
	{
		ft_putstr_fd("mvshell: exit: abc: numeric argument required", 2);
		exit(255);
	}
	else
		exit(ft_atoi(chunk[1]));
}
/*
int main(void)
{
	char **chunk = mvs_split("exit \"    2055    \"");
	printf("%s\n", chunk[0]);
	printf("%s\n", chunk[1]);
	mvs_exit(chunk);
}
 */