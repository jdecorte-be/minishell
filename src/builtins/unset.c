#include "builtins.h"


// void delnode(t_list **todel, char *var)
// {
//     if(todel == NULL)
//         return;
//     t_list *tmp = *todel;

//     if(ft_strcmp(ft_substr(tmp->content, 0, ft_strlen(var)), var) == 0)
//     {
//         *todel = tmp->next;
//         free(tmp);
//         return ;
//     }
//     while(tmp->next != NULL && ft_strcmp(ft_substr(tmp->next->content, 0, ft_strlen(var)), var))
//         tmp = tmp->next;
//     if(tmp == NULL || tmp->next == NULL)
//         return;
//     t_list *next  = tmp->next->next;
//     free(tmp->next);
//     tmp->next = next; 

// }


int unset(char **cmd, t_env *data)
{
    if(!cmd[1])
        return 0;
    int i = 1;
    while(cmd[++i])
    {
        free(getenv(cmd[i]));
    }
    return 0;
}