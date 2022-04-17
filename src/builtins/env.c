#include "builtins.h"

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

int unset(char **cmd, t_env *data)
{
	(void) data;
    if(!cmd[1])
        return 0;
    int i = 1;
    while(cmd[++i])
    {
        free(getenv(cmd[i]));
    }
    return 0;
}