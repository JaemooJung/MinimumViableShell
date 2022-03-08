#include "minishell.h"

int	parser(t_token **tokens, t_ast_node **tree)
{
	if (parse_pipeline(tree, tokens))
		return (1);
	return (0);
}

// 이상한 인풋
// cat "hello=ewjjdf ejsidjfi efsd f"