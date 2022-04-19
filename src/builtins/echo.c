# include "../../inc/minishell.h"

int echo(char **cmd)
{
	int i;
    int j = 1;
    int option = 0;

	i = 1;
    if(!cmd[1])
    {
        ft_putstr_fd("\n", 1);
        return 0;
    }
    while(cmd[i][0] == '-')
    {
        j = 1;
        while(cmd[i][j] && cmd[i][j] == 'n')
            j++;
        if(cmd[i][j] == '\0')
        {
            i++;
            option = 1;
        }
        else
            break;
    }
    while(cmd[i])
    {
        ft_putstr_fd(cmd[i], 1);
        if(cmd[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    if(option == 0)
        ft_putstr_fd("\n", 1);
    return 0;
}