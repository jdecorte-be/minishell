#include "../../inc/minishell.h"

void	test(int i)
{
	write(1, "  \b\b\ncaca->  \b\b  \b\b", 19);
}

void	ft_signal(int sig)
{
	int i = 10;

	if (sig == SIGINT)
	{
		signal(SIGINT, &test);
	}
}
