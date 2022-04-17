#include "../inc/minishell.h"

void sigtstp(int sig)
{
    (void)sig;
}

void	sig_handler(int sig)
{
    if(sig == SIGINT)
    {
        ft_putstr_fd("\n", 1);
        ft_putstr_fd(prompt(), 1);
    }
    else if(sig == SIGTSTP)
        ft_putstr_fd("\b\b", 1);
	// if (sig == SIGINT)
	// 	signal(sig, &ft_newprompt);
	// if (sig == SIGQUIT)
	// 	signal(SIGQUIT, &ft_exit_c_loop);
}