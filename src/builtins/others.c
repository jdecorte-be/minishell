#include "../../inc/minishell.h"

int unset(char **cmd, t_data *data)
{
	(void) data;
    if(!cmd[1])
        return 0;
    int i = 1;
    while(cmd[++i])
        printf("%s", cmd[i]);
    return 0;
}