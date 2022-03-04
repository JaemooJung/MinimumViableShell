#include "minishell.h"

int	main(int argc, char **argv)
{
	t_ast_node	*tree;

	argc++;
	tree = NULL;
	if (parse_user_input(argv[1], &tree))
		return (1);
}
