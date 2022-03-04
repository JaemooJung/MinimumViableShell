/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemoojung <jaemoojung@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 20:11:31 by jaemoojung        #+#    #+#             */
/*   Updated: 2022/03/03 02:05:10 by jaemoojung       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_command(t_token **tokens, t_ast_node **tree)
{
	if ((*tokens)->type == T_WORD)
	{
		while ((*tokens)->type == T_WORD)
		{
			*tree = ast_insert(*tree, (*tokens));
			(*tokens)++;
		}
		return (0);
	}
	else
		return (0);
}

int parse_redirection(t_token **tokens, t_ast_node **tree)
{
	t_ast_node	*redirection;

	parse_command(tokens, tree);
	if ((*tokens)->type == T_REDIRECTION)
	{
		redirection = make_ast_node((*tokens));
		if ((*tree)->token->type == T_WORD)
		{
			redirection->left = *tree;
			*tree = redirection;
		}
		else
		{
			(*tree)->right = redirection;
		}
		redirection->left = *tree;
		*tree = redirection;
		(*tokens)++;
		parse_redirection(tokens, tree);
	}
	return (0);
}

int	parse_pipeline(t_token **tokens, t_ast_node **tree)
{
	t_ast_node	*pipeline;

	parse_redirection(tokens, tree);
	if ((*tokens)->type == T_PIPE)
	{
		pipeline = make_ast_node((*tokens));
		pipeline->left = *tree;
		*tree = pipeline;
		(*tokens)++;
		parse_pipeline(tokens, tree);
	}
	return (0);
}

void	print_parsed(t_ast_node *tree)
{
	if (tree)
	{
		printf("value: %s\n", tree->token->value);
		print_parsed(tree->left);
		print_parsed(tree->right);
	}
}

// 하향파싱은 하향으로 짜야헌다... 개짓거리했음.. 시부랄...

int	parser(t_token **tokens, t_ast_node **tree)
{
	parse_pipeline(tokens, tree);
	print_parsed(*tree);
	return (0);
}