/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemoojung <jaemoojung@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 20:11:31 by jaemoojung        #+#    #+#             */
/*   Updated: 2022/03/06 22:41:43 by jaemoojung       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_token **tokens, t_ast_node **tree)
{
	if (parse_pipeline(tree, tokens))
		return (1);
	print_parsed(*tree);
	return (0);
}
