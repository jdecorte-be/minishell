# include "../../inc/minishell.h"

int echo(char **args)
{
	int i;
    int option = 0;
	i = 1;
    if(args[1])
    {
        while(args[i][0] == '-' && args[i][1] == 'n')
        {
            option = 1;
            i++;
        }
        while(args[i])
        {
            ft_putstr_fd(args[i], 1);
            if(args[i + 1])
                ft_putstr_fd(" ", 1);
            i++;
        }
        if(option == 0)
            ft_putstr_fd("\n", 1);
    }
    else
        ft_putstr_fd("\n", 1);
    return 0;
}