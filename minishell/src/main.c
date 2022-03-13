#include "minishell.h"

void	minimum_viable_shell(t_list *env)
{
	char		*cmdline;
	t_ast_node	*tree;
	int			err_code;

	tree = NULL;
	cmdline = readline("\033[1;32mminishell $ \033[0m");
	if (cmdline == NULL)
		return ;
	if (cmdline[0] != '\0')
		add_history(cmdline);
	err_code = parse_user_input(cmdline, &tree, env);
	if (err_code)
	{
		if (err_code == UNCLOSED_QUOTE)
			printf("ERROR: Unclosed quote\n");
		clear_ast(tree);
		ft_free_str(cmdline);
		return ;
	}
	print_parsed(tree);
	//run_tokens(tree, env);
	clear_ast(tree);
	ft_free_str(cmdline);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*our_env;

	printf("Hello, world!\n");
	printf("hello, minishell!\n");
//	setup_signals();
	our_env = envp_to_ours(envp);
	while (1)
	{
		minimum_viable_shell(our_env);
	}
}
