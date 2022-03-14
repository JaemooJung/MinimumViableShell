#include "minishell.h"

void	minimum_viable_shell(t_list *env)
{
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
	while (1)
	{
		minimum_viable_shell(our_env);
	}
}
