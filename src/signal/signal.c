#include "../../inc/minishell.h"

void	newprompt(int sig)
{
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void c_handler(int sig)
{
	newprompt(sig);
}

void c_handler_fork(int sig)
{
    printf("^C\n");
    rl_on_new_line();
}

void q_handler_fork(int sig)
{
    printf("^\\\n");
    rl_on_new_line();
}

void c_handler_doc(int sig)
{
    kill(data->pid, SIGINT);
    newprompt(0);
}


