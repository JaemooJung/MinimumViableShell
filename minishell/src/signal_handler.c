#include "minishell.h"

void	handle_sigint(pid_t pid)
{
	if (pid == -1)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		ft_putstr_fd("\n", 2);
}

void	handle_sigquit(pid_t pid)
{
	if (pid == -1)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \b\b", 2);
	}
	else
		ft_putstr_fd("Quit: 3\n", 2);
}

void	signal_handler(int signo)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signo == SIGINT)
		handle_sigint(pid);
	else if (signo == SIGQUIT)
		handle_sigquit(pid);
}

void	signal_handler_init(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}