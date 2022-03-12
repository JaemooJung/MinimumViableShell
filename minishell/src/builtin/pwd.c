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

int	mvs_pwd(char **chunk, t_list *env)
{
	char	*current_dir;

	(void)env;
	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
	{
		ft_print_error("pwd", NULL, strerror(errno));
		return (FAILURE);
	}
	printf("%s\n", current_dir);
	ft_free_str(current_dir);
	return (SUCCESS);
}
