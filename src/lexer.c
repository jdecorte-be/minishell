#include "../inc/minishell.h"


int exit_cmd(char **s_cmd)
{
        int i  = 0;
        while(s_cmd[1][i])
        {
            if(!ft_isdigit(s_cmd[1][i]))
                return 255;
            i++;
        }
        // printf("exit\n");
        if(s_cmd[2])
        {
            ft_putstr_fd("bash: exit: too many arguments\n", 2);
            return 1;
        }
        else if (s_cmd[1][0] == '+' && ft_isdigit(s_cmd[1][1]))
            return 0;
        else if (s_cmd[1][0] == '-' && ft_isdigit(s_cmd[1][1]))
            return 2;
        else if ((s_cmd[1][0] == '-' || s_cmd[1][0] == '+') && (s_cmd[1][1] == '-' || s_cmd[1][1] == '+') || s_cmd[1][0] == '-'  && ft_isdigit(s_cmd[1][1]))
            return 255;
        exit(ft_atoi(s_cmd[1]));

        return 0;
}

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
    else if(ft_strcmp(s_cmd[0], "exit") == 0)
        return exit_cmd(s_cmd);
    else
        return pipex(d_env, cmd);
    return 0;
}
