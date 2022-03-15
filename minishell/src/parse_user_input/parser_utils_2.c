/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemoojung <jaemoojung@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 22:41:08 by jaemoojung        #+#    #+#             */
/*   Updated: 2022/03/15 13:55:56 by jaemoojung       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*make_argv(t_token **token)
{
	t_list	*argv;
	t_list	*tmp;
	
	argv = NULL;
	while ((*token)->type == T_WORD)
	{
		tmp = ft_lstnew(ft_strdup((*token)->value));
		if (tmp == NULL)
			return (NULL);
		ft_lstadd_back(&argv, tmp);
		(*token)++;
	}
	return (argv);
}

// char	*conv_str_join(char *argv, char *new_str)
// {
// 	char	*tmp;

// 	tmp = argv;
// 	argv = j_strjoin(argv, new_str);
// 	if (argv == NULL)
// 		return (NULL);
// 	if (tmp != NULL)
// 	{
// 		free(tmp);
// 		tmp = NULL;
// 	}
// 	return (argv);
// }

// char	*make_argv(t_token **tokens)
// {
// 	char	*argv;

// 	argv = NULL;
// 	while ((*tokens)->type == T_WORD)
// 	{
// 		argv = conv_str_join(argv, (*tokens)->value);
// 		if (argv == NULL)
// 			return (NULL);
// 		if ((*tokens)[1].type == T_WORD)
// 			argv = conv_str_join(argv, " ");
// 		if (argv == NULL)
// 			return (NULL);
// 		(*tokens)++;
// 	}
// 	return (argv);
// }

void	print_parsed(t_ast_node *tree)
{
	t_list	*tmp;

	if (tree)
	{
		printf("type: %2d\n\tfile_path: %s\n", tree->node_type, tree->file_path);
		tmp = tree->argv;
		while (tmp)
		{
			printf("\targv: %s\n", tmp->line);
			tmp = tmp->next;
		}
		print_parsed(tree->left);
		print_parsed(tree->right);
	}
}
