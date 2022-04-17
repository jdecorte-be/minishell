#include "../inc/minishell.h"

int check_ope(char *ope)
{
    if(ft_strcmp(ope, "&&") == 0)
        return 1;
    if(ft_strcmp(ope, "||") == 0)
        return 2;
    if(ft_strcmp(ope, "|") == 0)
        return 3;
    return 0;
}

// return the return code of each command
int cmdlexer(char **cmd, t_env *d_env)
{
    if(check_ope(cmd[0]))
        return 0;
    if(ft_strcmp(cmd[0], "echo") == 0)
        return echo(cmd);
    else if(ft_strcmp(cmd[0], "cd") == 0)
        return cd(cmd);
    else if(ft_strcmp(cmd[0], "pwd") == 0)
        return pwd();
    else if(ft_strcmp(cmd[0], "env") == 0)
        return printList(d_env->l_env);
    else if(ft_strcmp(cmd[0], "export") == 0)
        return export(cmd, d_env);
    else if(ft_strcmp(cmd[0], "unset") == 0)
        return unset(cmd, d_env);
    else if(ft_strncmp(cmd[0], "exit", 4) == 0)
    {
        exit(1);
        printf("exit\n");
        return 0;
    }
    // else
    //     r_val = pipex(d_env, cmd);
    return 0;
}
