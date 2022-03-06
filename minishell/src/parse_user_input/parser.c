/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemoojung <jaemoojung@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 20:11:31 by jaemoojung        #+#    #+#             */
/*   Updated: 2022/03/06 20:28:54 by jaemoojung       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*conv_str_join(char *argv, char *new_str)
{
	char *tmp;

	tmp = argv;
	argv = ft_strjoin(argv, new_str);
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
		if ((*tokens)[1].type == T_WORD)
			argv = conv_str_join(argv, " ");
		(*tokens)++;
	}
	return (argv);
}

int	parse_command(t_ast_node **root, t_token **tokens)
{
	t_ast_node	*command;
	t_ast_node	*file_path;
	t_ast_node	*argv;

	command = make_ast_node(NODE_COMMAND, NULL);
	*root = ast_insert_node(*root, command, RIGHT);
	if ((*tokens)->type == T_WORD)
	{
		file_path = make_ast_node(NODE_FILE_PATH, ft_strdup((*tokens)->value));
		argv = make_ast_node(NODE_ARGV, make_argv(tokens));
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
	*root = ast_insert_node(*root, io_redirect, LEFT);
	if ((*tokens)->type == T_REDIRECTION)
	{
		redir_type = make_ast_node(NODE_REDIR_TYPE, ft_strdup((*tokens)->value));
		(*tokens)++;
		file_name = make_ast_node(NODE_FILE_NAME, make_argv(tokens));
		io_redirect->left = redir_type;
		io_redirect->right = file_name;
		return (0);
	}
	else
	{
		return (0);
	}
}

int parse_redirections(t_ast_node **root, t_token **tokens)
{
	t_ast_node	*redirections;

	//새 노드를 판다
	redirections = make_ast_node(NODE_REDIRS, NULL);
	//노드를 트리에 삽입한다. 얘는 아래에 io_redirect가 없으면 왼쪽으로, 있으면 오른쪽으로 삽입
	if ((*root)->left == NULL)
		*root = ast_insert_node(*root, redirections, LEFT);
	else
		*root = ast_insert_node(*root, redirections, RIGHT);
	parse_io_redirect(&redirections, tokens);
	if ((*tokens)->type == T_REDIRECTION)
	{
		parse_redirections(&redirections, tokens);
	}
	return (0);
}

int parse_phrase(t_ast_node **root, t_token **tokens)
{
	t_ast_node *phrase;
	
	//새 노드를 판다
	phrase = make_ast_node(NODE_PHRASE, NULL);
	//노드를 트리에 삽입한다. 근데 얘는 무조건 왼쪽으로 들어가야함.
	*root = ast_insert_node(*root, phrase, LEFT);
	parse_command(&phrase, tokens);
	if ((*tokens)->type == T_REDIRECTION)
	{
		parse_redirections(&phrase, tokens);
	}
	return (0);
}

int	parse_pipeline(t_ast_node **root, t_token **tokens)
{
	t_ast_node *pipeline;
	
	//새 노드를 판다
	pipeline = make_ast_node(NODE_PIPE, NULL);
	//노드를 트리에 삽입한다. 근데 얘는 무조건 오른쪽으로 들어가야함.
	*root = ast_insert_node(*root, pipeline, RIGHT);
	parse_phrase(&pipeline, tokens);
	if ((*tokens)->type == T_PIPE)
	{
		(*tokens)++;
		parse_pipeline(root, tokens);
	}
	return (0);
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

// 하향파싱은 하향으로 짜야헌다... 개짓거리했음.. 시부랄...

int	parser(t_token **tokens, t_ast_node **tree)
{
	parse_pipeline(tree, tokens);
	print_parsed(*tree);
	return (0);
}
