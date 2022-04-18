#include "../../inc/minishell.h"

int del_element(char *name)
{
    char **p_env = data->env;
    char **p_env2;

    while(*p_env)
    {
        if(ft_strncmp(*p_env, name, ft_strlen(name) - 1) == 0)
        {
            p_env2 = p_env;
            while(*p_env2)
            {
                *p_env2 = *(p_env2 + 1);
                p_env2++;
            }
        }
        p_env++;
    }
    return 0;
}

int unset(char **cmd)
{
    int offset;
    if(!cmd[1])
        return 0;
    int i = 1;
    while(cmd[i])
    {
        del_element(ft_ecrase_q(cmd[i]));
        i++;
    }
    return 0;
}