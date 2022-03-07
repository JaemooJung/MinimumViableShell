/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemoojung <jaemoojung@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 22:41:08 by jaemoojung        #+#    #+#             */
/*   Updated: 2022/03/07 15:27:49 by jaemoojung       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*conv_str_join(char *argv, char *new_str)
{
	char	*tmp;

	tmp = argv;
	argv = j_strjoin(argv, new_str);
	if (argv == NULL)
		return (NULL);
	if (tmp != NULL)
	{
		free(tmp);
		tmp = NULL;
	}
	return (argv);
}

char	*make_argv(t_token **tokens)
{
	char	*argv;

	argv = NULL;
	while ((*tokens)->type == T_WORD)
	{
		argv = conv_str_join(argv, (*tokens)->value);
		if (argv == NULL)
			return (NULL);
		if ((*tokens)[1].type == T_WORD)
			argv = conv_str_join(argv, " ");
		if (argv == NULL)
			return (NULL);
		(*tokens)++;
	}
	return (argv);
}

void	print_parsed(t_ast_node *tree)
{
	if (tree)
	{
		printf("value: %s\n", tree->content);
		print_parsed(tree->left);
		print_parsed(tree->right);
	}
}
