#include "minishell.h"

void	extract_remainder(t_list *content, t_list **remainder)
{
	if (ft_lstsize(content) < 2)
		return ;
	ft_lstadd_back(remainder, content->next);
	content->next = NULL;
}

void	dup_first_word(t_ast_node *node, t_list **remainder)
{
	node->file_path = ft_strdup((*remainder)->line);
	if (node->file_path == NULL)
		return ;
}

void	dup_remainder(t_ast_node *node, t_list **remainder)
{
	node->argv = *remainder;
}

void	open_nodes(t_ast_node *node)
{
	char	**temp;
	int		i;

	i = 0;
	if (node->left->left->right)
	{
		if (ft_lstsize(node->left->left->right->argv) < 2)
			return ;
		node->right->left = make_ast_node(NODE_FILE_PATH, NULL, NULL);
		node->right->right = make_ast_node(NODE_ARGV, NULL, NULL);
	}
}

bool	is_the_case(t_ast_node *node)
{
	if (node == NULL)
		return (false);
	if (node->left == NULL)
		return (false);
	if (node->left->left == NULL)
		return (false);
	if (node->left->left->left == NULL)
		return (false);
	if (node->left->right->left != NULL)
		return (false);
	return (true);
}

bool	is_in_the_case(t_ast_node *node)
{
	if (node->left == NULL)
		return (false);
	if (node->left->left == NULL)
		return (false);
	if (node->left->left->left == NULL)
		return (false);
	if (node->right->left != NULL)
		return (false);
	return (true);
}

void	search_for_remainder(t_ast_node *node, t_list **remainder)
{
	if (node->node_type == NODE_PHRASE && is_in_the_case(node) == true)
		open_nodes(node);
	else if (node->node_type == NODE_PHRASE && is_in_the_case(node) == false)
		return ;
	else if (node->node_type == NODE_FILE_NAME && node->argv != NULL)
		extract_remainder(node->argv, remainder);
	else if (node->node_type == NODE_FILE_PATH && node->file_path == NULL)
		dup_first_word(node, remainder);
	else if (node->node_type == NODE_ARGV && node->argv == NULL)
		dup_remainder(node, remainder);
	if (node->left != NULL)
		search_for_remainder(node->left, remainder);
	if (node->right != NULL)
		search_for_remainder(node->right, remainder);
}

void	collect_remainders(t_ast_node *tree)
{
	t_list *remainder;

	if (is_the_case(tree) == false)
		return ;
	remainder = NULL;
	search_for_remainder(tree, &remainder);
}

void ft_print_lst(t_list *lst)
{
	while (lst != NULL)
	{
		printf("%s\n", lst->line);
		lst = lst->next;
	}
}

void	minimum_viable_shell(t_list *env)
{
	static int	exit_status;
	char		*cmdline;
	t_ast_node	*tree;
	int			err_code;

	tree = NULL;
	cmdline = readline("\033[1;32mminishell $ \033[0m");
	//ctrl+d가 들어왓을 때 readline 값은 NULL이 된다..
	if (cmdline == NULL)
	{
		printf("\033[1A"); // 커서를 위로 한 줄 올린다.
		printf("\033[10C"); // 커서를 10만큼 앞으로 전진시킨다.
		printf("exit\n");
		exit(0);
	}
	if (cmdline[0] != '\0')
		add_history(cmdline);
	err_code = parse_user_input(cmdline, &tree, env, exit_status);
	if (err_code)
	{
		if (err_code == UNCLOSED_QUOTE)
			printf("ERROR: Unclosed quote\n");
		clear_ast(tree);
		ft_free_str(cmdline);
		return ;
	}
	print_parsed(tree);
	collect_remainders(tree);
	print_parsed(tree);
	run_tokens(tree, env, &exit_status);
	clear_ast(tree);
	ft_free_str(cmdline);
}

int	main(int argc, char **argv, char **envp)
{
	t_list			*our_env;
	struct termios	term;
	
	printf("Hello, world!\n");
	printf("hello, minishell!\n");
	//현재 터미널의 속성을 읽어와서 term 구조체에 저장
	tcgetattr(STDIN_FILENO, &term);
	//터미널의 속성을 설정
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal_handler_init();
	our_env = envp_to_ours(envp);
	if (our_env == NULL)
		exit(ft_print_error(NULL, NULL, "Fatal error: initialization failed."));
	if (add_shlvl(our_env) == FAILURE)
		exit(ft_print_error(NULL, NULL, "Fatal error: initialization failed."));
	while (1)
		minimum_viable_shell(our_env);
}
