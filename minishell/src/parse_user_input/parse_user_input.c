
#include "minishell.h"

static void	free_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].type != T_NULL)
	{
		free(tokens[i].value);
		tokens[i].value = NULL;
		i++;
	}
	free(tokens);
}

static void	free_vector(char **vector)
{
	int	i;

	i = 0;
	while (vector[i])
	{
		free(vector[i]);
		vector[i] = NULL;
		i++;
	}
	free(vector);
}

int	parse_user_input(const char *input, t_ast_node **tree, t_list *our_env)
{
	char	**splitted;
	t_token	*tokens;
	t_token	*tmp;

	splitted = mvs_split(input);
	debug_print_vector(splitted);
	lexer(splitted, &tokens);
	tmp = tokens;
	debug_print_tokens(tmp);
	parser(&tmp, tree);
	expand_env(tree, our_env);
	free_tokens(tokens);
	free_vector(splitted);
	return (0);
}
