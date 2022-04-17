#include "minishell.h"
#include <stdio.h>

int main(int ac, char **av, char **env)
{
    (void)av;
    if(ac == 1)
    {

        while(1)
        {
            char *input = readline("> ");
            exec(input, env);

        }
    }
}