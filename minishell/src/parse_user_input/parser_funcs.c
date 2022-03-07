/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemoojung <jaemoojung@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 22:38:50 by jaemoojung        #+#    #+#             */
/*   Updated: 2022/03/06 22:54:05 by jaemoojung       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_command(t_ast_node **root, t_token **tokens)
{
	t_ast_node	*command;
	t_ast_node	*file_path;
	t_ast_node	*argv;

	command = make_ast_node(NODE_COMMAND, NULL);
	if (command == NULL)
		return (1);
	*root = ast_insert_node(*root, command, RIGHT);
	if ((*tokens)->type == T_WORD)
	{
		file_path = make_ast_node(NODE_FILE_PATH, ft_strdup((*tokens)->value));
		argv = make_ast_node(NODE_ARGV, make_argv(tokens));
		if (file_path->content == NULL || argv->content == NULL)
			return (1);
		command->left = file_path;
		command->right = argv;
		return (0);
	}
	else
		return (0);
}

int	parse_io_redirect(t_ast_node **root, t_token **tokens)
{
	t_ast_node	*io_redirect;
	t_ast_node	*redir_type;
	t_ast_node	*file_name;

	io_redirect = make_ast_node(NODE_IO_REDIR, NULL);
	if (io_redirect == NULL)
		return (1);
	*root = ast_insert_node(*root, io_redirect, LEFT);
	if ((*tokens)->type == T_REDIRECTION)
	{
		redir_type = make_ast_node(NODE_REDIR_TYPE,
				ft_strdup((*tokens)->value));
		(*tokens)++;
		file_name = make_ast_node(NODE_FILE_NAME, make_argv(tokens));
		io_redirect->left = redir_type;
		io_redirect->right = file_name;
	}
	return (0);
}

int	parse_redirections(t_ast_node **root, t_token **tokens)
{
	t_ast_node	*redirections;

	redirections = make_ast_node(NODE_REDIRS, NULL);
	if (redirections == NULL)
		return (1);
	if ((*root)->left == NULL)
		*root = ast_insert_node(*root, redirections, LEFT);
	else
		*root = ast_insert_node(*root, redirections, RIGHT);
	if (parse_io_redirect(&redirections, tokens))
		return (1);
	if ((*tokens)->type == T_REDIRECTION)
	{
		if (parse_redirections(&redirections, tokens))
			return (1);
	}
	return (0);
}

int	parse_phrase(t_ast_node **root, t_token **tokens)
{
	t_ast_node	*phrase;

	phrase = make_ast_node(NODE_PHRASE, NULL);
	if (phrase == NULL)
		return (1);
	*root = ast_insert_node(*root, phrase, LEFT);
	if (parse_command(&phrase, tokens))
		return (1);
	if ((*tokens)->type == T_REDIRECTION)
	{
		if (parse_redirections(&phrase, tokens))
			return (1);
	}
	return (0);
}

int	parse_pipeline(t_ast_node **root, t_token **tokens)
{
	t_ast_node	*pipeline;

	pipeline = make_ast_node(NODE_PIPE, NULL);
	if (pipeline == NULL)
		return (1);
	*root = ast_insert_node(*root, pipeline, RIGHT);
	if (parse_phrase(&pipeline, tokens))
		return (1);
	if ((*tokens)->type == T_PIPE)
	{
		(*tokens)++;
		if (parse_pipeline(root, tokens))
			return (1);
	}
	return (0);
}
