# include "../../inc/minishell.h"

void print_exp(t_data *data)
{
    int len = splitlen(data->env);
    int i = 0;
    while(i < len)
    {
        int j = i+1;
        while (++j < len)
            if (ft_strcmp(data->env[i], data->env[j]) > 0 && data->env[i] && data->env[j]) {
                char* temp = data->env[i]; 
                data->env[i] = data->env[j]; 
                data->env[j] = temp; 
             }
             if(data->env[i])
                printf("declare -x %s\n", data->env[i]);
        i++;
    }
}

int export(char **cmd,t_data *data)
{
    if(!cmd[1])
    {
        print_exp(data);
        return 0;
    }
    int i = 0;
    while(cmd[1][i] && cmd[1][i] != '=')
        i++;
    char *var = getenv(ft_substr(cmd[1], 0, i));
    if(var)
        ft_memcpy(var, ft_substr(cmd[1], i + 1, ft_strlen(cmd[1])), ft_strlen(cmd[1]));
    else
        my_setenv(ft_substr(cmd[1], 0, i), ft_substr(cmd[1], i + 1, ft_strlen(cmd[1])));

    return 0;
}
