/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msv_split_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 20:14:49 by hakim             #+#    #+#             */
/*   Updated: 2022/02/28 20:14:50 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	m_is_space(char c)
{
	if (c == SPACE || (9 <= c && c <= 13))
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
