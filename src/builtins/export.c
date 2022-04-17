#include "builtins.h"

int check_format(char *str)
{
    int i = 0;
    while(str[i] != '=' && str[i])
        i++;
    if(str[i] != '=')
        return 1;
    if(str[i] == '=')
        return 2;
    return 0;
}

void print_sort_exp(char **env, t_env *data)
{
    int len = ft_lstsize(data->l_exp);
    int i = 0;
    while(i < len)
    {
        int j = i+1;
        while (++j < len)
            if (ft_strcmp(env[i], env[j]) > 0 && env[i] && env[j]) {
                char* temp = env[i]; 
                env[i] = env[j]; 
                env[j] = temp; 
             }
             if(env[i])
                printf("declare -x %s\n", env[i]);
        i++;
    }
}

int export(char **cmd,t_env *data)
{
    if(!cmd[1])
    {
        print_sort_exp(listtotab(data->l_exp), data);
        return 0;
    }
    int i = 1;
    while(cmd[i])
    {
        // if(checkvalid(cmd[i]) != -1 || checkvalid(cmd[i]) != 1)
        //     return 0;
        char *str = my_getenv(cmd[i], data->l_exp);
        printf("export %s\n", str);
        if(str != NULL)
        {
            t_list *new3 = ft_lstnew(cmd[i]);
            unset(cmd, data);
            ft_lstadd_back(&data->l_env, new3);
        }
        else if(check_format(cmd[i]) == 1)
        {
            printf("OK1");
            t_list *new1 = ft_lstnew(ft_strjoin(cmd[i], "=\'\'"));
            ft_lstadd_back(&data->l_exp, new1);
        }
        else if(check_format(cmd[i]) == 2)
        {
            printf("OK2");
            t_list *new2 = ft_lstnew(cmd[i]);
            ft_lstadd_back(&data->l_env, new2);
            ft_lstadd_back(&data->l_exp, new2);
        }
        i++;
    }
    return 0;
}
