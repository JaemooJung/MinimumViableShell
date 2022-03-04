/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemoojung <jaemoojung@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:48:43 by jaemoojung        #+#    #+#             */
/*   Updated: 2022/03/03 00:15:51 by jaemoojung       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: 트리 할당 실패했을 때 에러처리 어케할건지?

t_ast_node	*make_ast_node(t_token *token)
{
	t_ast_node	*node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!node)
		exit(MALLOC_ERROR);
	node->token = token;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast_node	*ast_insert(t_ast_node *root, t_token *token)
{
	if (root == NULL)
	{
		root = make_ast_node(token);
		return (root);
	}
	else
	{
		if (root->left == NULL)
			root->left = ast_insert(root->left, token);
		else
			root->right = ast_insert(root->right, token);
		return (root);
	}
}