/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemoojung <jaemoojung@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:48:43 by jaemoojung        #+#    #+#             */
/*   Updated: 2022/03/08 20:49:54 by jaemoojung       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO: 트리 할당 실패했을 때 에러처리 어케할건지?

t_ast_node	*make_ast_node(int node_type, char *content)
{
	t_ast_node	*node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (node == NULL)
		return (NULL);
	node->node_type = node_type;
	node->content = content;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

// t_ast_node	*ast_insert(t_ast_node *root, t_token *token, int side)
// {
// 	if (root == NULL)
// 	{
// 		root = make_ast_node(token);
// 		return (root);
// 	}
// 	else
// 	{
// 		if (root->left == NULL)
// 			root->left = ast_insert(root->left, token, side);
// 		else
// 			root->right = ast_insert(root->right, token, side);
// 		return (root);
// 	}
// }

t_ast_node	*ast_insert_node(t_ast_node *root, t_ast_node *node, int side)
{
	if (root == NULL)
	{
		root = node;
		return (root);
	}
	else
	{
		if (side == LEFT)
			root->left = ast_insert_node(root->left, node, side);
		else
			root->right = ast_insert_node(root->right, node, side);
		return (root);
	}
}

void	clear_ast(t_ast_node *root)
{
	if (root == NULL)
		return ;
	clear_ast(root->left);
	clear_ast(root->right);
	if (root->content != NULL)
	{
		free(root->content);
		root->content = NULL;
	}
	free(root);
	root = NULL;
}
