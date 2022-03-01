/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:34:48 by hakim             #+#    #+#             */
/*   Updated: 2022/03/01 14:34:49 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mvs_env(char **envp)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
		printf("%s\n", envp[i++]);
}
/*
int main(int ac, char **av, char **envp)
{
	mvs_env(envp);
}
 */