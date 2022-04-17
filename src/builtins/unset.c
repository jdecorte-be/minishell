#include "builtins.h"

void delnode(t_list *todel, char *var)
{
    while(todel->next && ft_strcmp(ft_substr(todel->content, 0, ft_strlen(var)), var))
        todel = todel->next;
    if(ft_strcmp(ft_substr(todel->content, 0, ft_strlen(var)), var) == 0)
    {
        ft_memdel(todel);
		todel->content = NULL;
		todel->content = NULL;
    }
}


int unset(char **cmd, t_env *data)
{
    if(!cmd[1])
        return 0;
    int i = 1;
    while(cmd[i])
    {
        int j = 0;
        while(cmd[i][j] != '=' && cmd[i][j] != '/' && cmd[i][j])
            j++;
        if(cmd[i][j] == '=' || cmd[i][j] == '/')
        {
            fprintf(stderr, "minishell: unset: %s: not a valid identifier\n", cmd[i]);
            return -1;
        }
        char *todel = ft_substr(cmd[i], 0, j);
        delnode(data->l_env, todel);
        delnode(data->l_exp , todel);
        i++;
    }
    return 0;
}