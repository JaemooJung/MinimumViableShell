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

static bool	is_white_space(char c)
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

t_stat	mvs_exit(char **chunk, t_list *env)
{
	int	i;

	(void)env;
	i = 0;
	while (chunk[i] != NULL)
		i++;
	if (i == 1)
	{
		ft_putstr_fd("exit\n", 1);
		exit(EXIT_SUCCESS);
	}
	if (i > 2)
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments", 2);
		return (FAILURE);
	}
	dequote(chunk[1]); // will be performed while parsing, so have to be deleted
	if (can_be_atoied(chunk[1]) == false)
	{
		ft_putstr_fd("exit\nminishell: exit: abc: numeric argument required", 2);
		exit(255);
	}
	ft_putstr_fd("exit\n", 1);
	exit(ft_atoi(chunk[1]));
}

int main(void)
{
	char **chunk = mvs_split("exit \"world");
	int index = 0;
	while (chunk[index] != NULL)
		printf("%s\n", chunk[index++]);
//	printf("%s\n", chunk[0]);
//	printf("%s\n", chunk[1]);
//	mvs_exit(chunk);
}
