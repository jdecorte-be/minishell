# include "../../inc/minishell.h"

int checkvalid(char *cmd)
{
    int i = 0;
    while(cmd[i])
    {
        if((ft_isalnum(cmd[i]) == 0 && cmd[i] != '\'' && cmd[i] != '"' && cmd[i] != '_') || ft_isdigit(cmd[0]) == 1 || cmd[0] == '=')
        {
            puterror(cmd, "not a valid identifier");
            return 0;
        }
        if(cmd[i] == '=')
            break;
        i++;
    }
    return 1;
}

char **array_dup(char **tab)
{
    char **res;
    int i = 0;

    res = malloc(sizeof(char *) * splitlen(data->env));
    while(i < splitlen(data->env))
    {
        res[i] = ft_strdup(data->env[i]);
        i++;
    }
    return res;
}

void export_print()
{
    int len = splitlen(data->env);
    char **env = array_dup(data->env);
    int i = 0;

    while(i < len)
    {
        int j = i + 1;
        while (++j < len)
            if (ft_strcmp(env[i], env[j]) > 0 && env[i] && env[j])
            {
                char* temp = env[i]; 
                env[i] = env[j]; 
                env[j] = temp; 
             }
             if(env[i])
                format_env(env[i]);
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
        if(!checkvalid(ft_ecrase_q(cmd[i])))
            return 0;
        my_setenv(ft_ecrase_q(cmd[i]));
        i++;
    }
    data->lastret = 0;
    return 0;
}
