# include "../../inc/minishell.h"

int echo(char **cmd)
{
	int i;
    int option = 0;

	i = 1;
    while(cmd[i] && cmd[i][0] == '-' && cmd[i][1] == 'n')
    {
        option = 1;
        i++;
    }
    while(cmd[i])
    {
        ft_putstr_fd(ft_ecrase_q(cmd[i]), 1);
        if(cmd[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    if(option == 0)
        ft_putstr_fd("\n", 1);

    return 0;
}