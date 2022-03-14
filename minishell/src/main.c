#include "minishell.h"
//
//void	extract_remainder(char *content, char *remainder)
//{
//	int		space_loc;
//	char	*temp;
//
//	if (ft_strchr(content, ' ') == NULL)
//		return ;
//	space_loc = 0;
//	while (content[space_loc] != ' ')
//		++space_loc;
//	temp = ft_strjoin(remainder, &content[space_loc]);
//	if (temp == NULL)
//		return ;
//	if (remainder != NULL)
//		ft_free_str(remainder);
//	remainder = temp;
//	content[space_loc] = '\0';
//}
//
//void	dup_first_word(t_ast_node *node, char *remainder)
//{
//	int		space_loc;
//
//	node->content = ft_strdup(remainder);
//	if (node->content == NULL)
//		return ;
//	space_loc = 0;
//	while (node->content[space_loc] != ' ' && node->content[space_loc] != '\0')
//		++space_loc;
//	node->content[space_loc] = '\0';
//}
//
//void	dup_remainder(t_ast_node *node, char *remainder)
//{
//	node->content = ft_strdup(remainder);
//	if (node->content == NULL)
//		return ;
//}
//
//void	search_for_remainder(t_ast_node *node, char *remainder)
//{
//	if (node->node_type == NODE_FILE_NAME)
//		extract_remainder(node->content, remainder);
//	else if (node->node_type == NODE_FILE_PATH && node->content == NULL)
//		dup_first_word(node, remainder);
//	else if (node->node_type == NODE_ARGV && node->content == NULL)
//		dup_remainder(node, remainder);
//	if (node->left != NULL)
//		search_for_remainder(node->left, remainder);
//	if (node->right != NULL)
//		search_for_remainder(node->right, remainder);
//}
//
//void	collect_remainders(t_ast_node *tree)
//{
//	char *remainder;
//
//	remainder = NULL;
//	search_for_remainder(tree, remainder);
//	ft_free_str(remainder);
//}

void	minimum_viable_shell(t_list *env)
{
	static int	exit_status = 0;
	char		*cmdline;
	t_ast_node	*tree;

	tree = NULL;
	cmdline = readline("\033[1;32mminishell $ \033[0m");
	if (cmdline == NULL)
		return ;
	if (cmdline[0] != '\0')
		add_history(cmdline);
	if (parse_user_input(cmdline, &tree, env))
	{
		clear_ast(tree);
		ft_free_str(cmdline);
		return ;
	}
//	print_parsed(tree);
//	collect_remainders(tree);
//	print_parsed(tree);
	run_tokens(tree, env, &exit_status);
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
	if (our_env == NULL)
		;
	if (add_shlvl(our_env) == FAILURE)
		;
	while (1)
	{
		minimum_viable_shell(our_env);
	}
}
