#include "minishell.h"

void	extract_remainder(char *content, char **remainder)
{
	int		space_loc;
	char	*temp;

	if (ft_strchr(content, ' ') == NULL)
		return ;
	space_loc = 0;
	while (content[space_loc] != ' ')
		++space_loc;
	if (*remainder != NULL)
	{
		temp = ft_strjoin(*remainder, " ");
		if (temp == NULL)
			return ;
		ft_free_str(*remainder);
		*remainder = temp;
	}
	temp = ft_strjoin(*remainder, &content[space_loc + 1]);
	if (temp == NULL)
		return ;
	if (*remainder != NULL)
		ft_free_str(*remainder);
	*remainder = temp;
	content[space_loc] = '\0';
}

void	dup_first_word(t_ast_node *node, char **remainder)
{
	int		space_loc;

	node->content = ft_strdup(*remainder);
	if (node->content == NULL)
		return ;
	space_loc = 0;
	while (node->content[space_loc] != ' ' && node->content[space_loc] != '\0')
		++space_loc;
	node->content[space_loc] = '\0';
}

void	dup_remainder(t_ast_node *node, char **remainder)
{
	node->content = ft_strdup(*remainder);
	if (node->content == NULL)
		return ;
	if (*remainder)
	{
		ft_free_str(*remainder);
		*remainder = NULL;
	}
}

void	open_nodes(t_ast_node *node)
{
	char	**temp;
	int		i;

	i = 0;
	if (node->left->left->right)
	{
		temp = ft_split(node->left->left->right->content, ' ');
		if (temp == NULL)
			return ;
		while (temp[i] != NULL)
			++i;
		ft_free_vector(temp);
		if (i < 2)
			return ;
		node->right->left = make_ast_node(NODE_FILE_PATH, NULL);
		node->right->right = make_ast_node(NODE_ARGV, NULL);
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
//	if (node->left->left->left->left == NULL)
//		return (false);
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

void	search_for_remainder(t_ast_node *node, char **remainder)
{
	if (node->node_type == NODE_PHRASE && is_in_the_case(node) == true)
		open_nodes(node);
	else if (node->node_type == NODE_PHRASE && is_in_the_case(node) == false)
		return ;
	else if (node->node_type == NODE_FILE_NAME)
		extract_remainder(node->content, remainder);
	else if (node->node_type == NODE_FILE_PATH && node->content == NULL)
		dup_first_word(node, remainder);
	else if (node->node_type == NODE_ARGV && node->content == NULL)
		dup_remainder(node, remainder);
	if (node->left != NULL)
		search_for_remainder(node->left, remainder);
	if (node->right != NULL)
		search_for_remainder(node->right, remainder);
}

void	collect_remainders(t_ast_node *tree)
{
	char *remainder;

	if (is_the_case(tree) == false)
		return ;
	remainder = NULL;
	search_for_remainder(tree, &remainder);
	if (remainder != NULL)
		ft_free_str(remainder);
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
//	print_parsed(tree);
	collect_remainders(tree);
//	print_parsed(tree);
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
