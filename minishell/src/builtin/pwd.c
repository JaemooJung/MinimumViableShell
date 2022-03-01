/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:34:35 by hakim             #+#    #+#             */
/*   Updated: 2022/03/01 14:34:36 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minilibft.c"

void	mvs_pwd(char **chunk)
{
	char *currentDir = getcwd(NULL, 0);
	printf("%s\n", currentDir);
	free(currentDir);
	currentDir = NULL;
}
/*
int main(void)
{
	char *chunk[2];

	chunk[0] = "pwd";
	chunk[1] = 0;
	mvs_pwd(chunk);
	system("leaks pwd");
}
*/