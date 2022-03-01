/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 13:57:06 by hakim             #+#    #+#             */
/*   Updated: 2022/03/01 13:57:08 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_opt(const char *arg, bool *nlflag, bool *optflag)
{
	int	index;

	if (*optflag == false)
		return (false);
	if (arg[0] != '-')
	{
		*optflag = false;
		return (false);
	}
	index = 1;
	while (arg[index] == 'n')
		++index;
	if (arg[index] == '\0')
	{
		*nlflag = false;
		return (true);
	}
	*optflag = false;
	return (false);
}

/* input should include the command, 'echo' */
void	mvs_echo(char **chunk)
{
	bool	nlflag;
	bool	optflag;
	int		index;

	index = 1;
	nlflag = true;
	optflag = true;
	while (chunk[index] != NULL)
	{
		if (is_valid_opt(chunk[index], &nlflag, &optflag) == false)
		{
			printf("%s", chunk[index]);
			if (chunk[index + 1] != NULL)
				printf(" ");
		}
		++index;
	}
	if (nlflag == true)
		printf("\n");
}

/*
int	main(void)
{
	char *str = "echo -n -nnnnnn 15345 -n 1345 -n -n -n-n-n 123123 585145";
	char **splitted = mvs_split(str);
	mvs_echo(splitted);
	exit(13);
}
*/