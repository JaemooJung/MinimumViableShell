/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemoojung <jaemoojung@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:34:02 by jaemoojung        #+#    #+#             */
/*   Updated: 2022/03/07 20:14:58 by jaemoojung       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_vector_size(char **vector)
{
	int	i;

	i = 0;
	while (vector[i])
		++i;
	return (i);
}

static int	get_token_type(char *token)
{
	if (token[0] == '|')
		return (T_PIPE);
	else if (token[0] == '>' || token[0] == '<')
		return (T_REDIRECTION);
	else if (token[0] == '\0')
		return (T_NULL);
	else
		return (T_WORD);
}

/*
*	parameter	: splitted user input (char **), token address (t_token **)
*	description : 
*	return		: 0 if success, 1 if fail
*/
int	lexer(char **splitted, t_token **tokens)
{
	int	i;

	*tokens = NULL;
	*tokens = (t_token *)malloc(sizeof(t_token)
			* (get_vector_size(splitted) + 1));
	if (!(*tokens))
		return (MALLOC_ERR);
	i = 0;
	printf("original value: %s\n", splitted[1]);
	printf("duplicated value: %s\n", ft_strdup(splitted[1]));
	while (splitted[i] != NULL)
	{
		printf("original value: %s\n", splitted[i]);
		printf("duplicated value: %s\n", ft_strdup(splitted[i]));
		(*tokens)[i].type = get_token_type(splitted[i]);
		(*tokens)[i].value = ft_strdup(splitted[i]);
		i++;
	}
	(*tokens)[i].type = T_NULL;
	(*tokens)[i].value = NULL;
	return (0);
}
