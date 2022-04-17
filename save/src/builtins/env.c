# include "../../inc/minishell.h"

char *my_getenv(char *name, t_data *data)
{
    int i = 0;

    while(data->env[i])
    {
        int j = 0;
        while(data->env[i][j] && data->env[i][j] != '=')
            j++;
        if(ft_strcmp(ft_substr(data->env[i], 0, j), name) == 0)
            return ft_substr(data->env[i], j + 1, ft_strlen(data->env[i]));
        i++;
    }
    return NULL;
}

int checkvalid(char *cmd)
{
    int i = 0;
    while(cmd[i])
    {
		if(cmd[0] != '=' && cmd[i] == '=')
			return -1;
        else if((ft_isalnum(cmd[i]) == 0 && cmd[i] != '\'' && cmd[i] != '"' && cmd[i] != '_') || ft_isdigit(cmd[0]) == 1)
        {
            printf("minishell: unset: %s: not a valid identifier\n", cmd);
            return 0;
        }
        i++;
    }
    return 1;
}

int print_env(char **env)
{
	int i = 0;
	while(env[++i])
		printf("%s\n", env[i]);
	return 0;
}

void delete_env(char *name, t_data *data)
{
    int i = 0;

    while(data->env[i])
    {
        int j = 0;
        while(data->env[i][j] != '=' && data->env[i][j])
            j++;
        if(ft_strcmp(ft_substr(data->env[i], 0, j), name) == 0)
            data->env[i] = data->env[i+1];
        i++;
    }
}

int unset(char **cmd, t_data *data)
{
	(void) data;
    if(!cmd[1])
        return 0;
    int i = 1;
    while(cmd[++i])
        delete_env(cmd[i], data);
    return 0;
}