# include "../../inc/minishell.h"

// * ok
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
        i++;
        if(cmd[i] == '=')
            break;
    }
    return 1;
}

// * fix malloc
char **array_dup(char **tab)
{
    char **res;
    int i = 0;

    res = malloc(sizeof(char *) * splitlen(data->env));
    if(!res)
        return NULL;
    while(i < splitlen(data->env))
    {
        res[i] = ft_strdup(data->env[i]);
        if(!res[i])
            return NULL;
        i++;
    }
    return res;
}

// * fix arrdup
void export_print()
{
    int len = splitlen(data->env);
    char **env;
    int i = 0;

    env = array_dup(data->env);
    if(env == NULL)
        return ;
    while(i < len)
    {
        int j = i + 1;
        while (++j < len)
            if (ft_strcmp(env[i], env[j]) > 0 && env[i] && env[j])
            {
                char *temp = env[i]; 
                env[i] = env[j]; 
                env[j] = temp; 
             }
             if(env[i])
                format_env(env[i]);
        i++;
    }
    ft_free_tab(env);
}

// *ok
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
        if(cmd[i][0] == '_' && cmd[i][1] == '=')
            return 0;
        if(!checkvalid(ft_ecrase_q(cmd[i])))
            return 0;
        my_setenv(ft_ecrase_q(cmd[i]), 1);
        i++;
    }
    data->lastret = 0;
    return 0;
}
