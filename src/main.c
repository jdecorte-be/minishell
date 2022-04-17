#include "minishell.h"
#include <stdio.h>

int main()
{
    while(1)
    {
        char *input = readline("> ");
        exec(input);

    }
}