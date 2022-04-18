# include "../../inc/minishell.h"

void export_print()
{
    int len = splitlen(data->env);
    int i = 0;
    while(i < len)
    {
        int j = i + 1;
        while (++j < len)
            if (ft_strcmp(data->env[i], data->env[j]) > 0 && data->env[i] && data->env[j]) {
                char* temp = data->env[i]; 
                data->env[i] = data->env[j]; 
                data->env[j] = temp; 
             }
             if(data->env[i])
                format_env(data->env[i]);
        i++;
    }
}

int export(char **cmd)
{
    if(!cmd[1])
    {
        export_print();
        return 0;
    }
    int i = 1;
    while(cmd[i])
    {
        my_setenv(cmd[i]);
        i++;
    }

    return 0;
}
