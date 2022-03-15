/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvs_split_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemoojung <jaemoojung@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:45:14 by jaemoojung        #+#    #+#             */
/*   Updated: 2022/03/15 15:45:16 by jaemoojung       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	m_is_space(char c)
{
	if (c == SPACE)
		return (true);
	return (false);
}

bool	m_is_quote(char c)
{
	if (c == SQUOTE || c == DQUOTE)
		return (true);
	return (false);
}

void	ft_free_split(char **splitted, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(splitted[i]);
		splitted[i] = 0;
		++i;
	}
	free(splitted);
	splitted = 0;
}
