#include "minishell.h"

int	parser(t_token **tokens, t_ast_node **tree)
{
	if (parse_pipeline(tree, tokens))
		return (1);
	return (0);
}
