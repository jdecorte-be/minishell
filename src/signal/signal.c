#include "../../inc/minishell.h"

void	ft_newprompt(int i)
{
	write(1, "    ", 4);
	write(1, "\n", 1);
	write(1, "caca->", 6);
	// exit(1);
}

void	ft_exit_d_loop(int i)
{
	write(1, "exit", 4);
	exit(i); // i = global
}

void	ft_exit_c_loop(int i)
{
	exit(130);
}

void	ft_exit_bs_loop(int i)
{
	write(1, "1\n", 2);
	// write(1, "Quit: 3", 7);
	// exit(131);
}

void	ft_nothing(int i)
{
}

void	ft_signal(int sig)
{
	int i = 10;

	if (sig == SIGINT)
		signal(sig, &ft_newprompt);
	if (sig == SIGQUIT)
		signal(SIGQUIT, &ft_exit_bs_loop);
}
