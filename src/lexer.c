#include "../inc/minishell.h"


// return the return code of each command
int cmdlexer(char *cmd, t_env *d_env)
{
    char **s_cmd = ft_split(cmd," ");
    if(ft_strcmp(s_cmd[0], "echo") == 0)
        return echo(s_cmd);
    else if(ft_strcmp(s_cmd[0], "cd") == 0)
        return cd(s_cmd);
    else if(ft_strcmp(s_cmd[0], "pwd") == 0)
        return pwd();
    else if(ft_strcmp(s_cmd[0], "env") == 0)
        return print_env(d_env->env);
    else if(ft_strcmp(s_cmd[0], "export") == 0)
        return export(s_cmd, d_env);
    else if(ft_strcmp(s_cmd[0], "unset") == 0)
        return unset(s_cmd, d_env);
    else if(ft_strncmp(s_cmd[0], "exit", 4) == 0)
    {
        printf("exit\n");
        if(s_cmd[2])
        {
            ft_putstr_fd("bash: exit: too many arguments", 2);
            return 1;
        }
        exit(ft_atoi(s_cmd[1]));
        return 0;
    }
    else
        return pipex(d_env, cmd);
    return 0;
}
