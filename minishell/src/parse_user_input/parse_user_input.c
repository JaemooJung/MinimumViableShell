/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_user_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemoojung <jaemoojung@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 20:57:26 by jaemoojung        #+#    #+#             */
/*   Updated: 2022/03/06 22:57:30 by jaemoojung       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_user_input(const char *input, t_ast_node **tree)
{
	char	**splitted;
	t_token	*tokens;
	t_token	*tmp;

	splitted = mvs_split(input);
	// debug_print_vector(splitted);
	lexer(splitted, &tokens);
	tmp = tokens;
	// debug_print_tokens(tmp);
	parser(&tmp, tree);
	return (0);
}
