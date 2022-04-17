/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: decortejohn <decortejohn@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:25:24 by decortejohn       #+#    #+#             */
/*   Updated: 2022/01/23 16:28:21 by decortejohn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int cmdlexer(char *cmd, t_data *d_env)
{
    char **s_cmd = ft_split(cmd," ");

    if(d_env->is_subshell == 1)
    {
        d_env->is_subshell = 0;
        d_env->lastret = subshell(cmd, d_env);
    }
    else if(ft_strcmp(s_cmd[0], "echo") == 0)
        d_env->lastret = echo(s_cmd);
    else if(ft_strcmp(s_cmd[0], "cd") == 0)
        d_env->lastret = cd(s_cmd, d_env);
    else if(ft_strcmp(s_cmd[0], "pwd") == 0)
        d_env->lastret = pwd();
    else if(ft_strcmp(s_cmd[0], "env") == 0)
        d_env->lastret = print_env(d_env->env);
    else if(ft_strcmp(s_cmd[0], "export") == 0)
        d_env->lastret = export(s_cmd, d_env);
    else if(ft_strcmp(s_cmd[0], "unset") == 0)
        d_env->lastret = unset(s_cmd, d_env);
    else if(ft_strcmp(s_cmd[0], "exit") == 0)
         exit_cmd(s_cmd);
    return -1;
}

char *get_path(char *cmd)
{
	int i;
	char **args = ft_split(cmd, " ");
	char *exec;
	char **allpath = ft_split(getenv("PATH"), ":");
	i = -1;
	if (access(args[0], X_OK) == 0)
		exec = args[0];
	else
	{
		while (allpath[++i])
		{
			allpath[i] = ft_strjoin(allpath[i], "/");
			exec = ft_strjoin(allpath[i], args[0]);
			free(allpath[i]);
			if (access(exec, F_OK | X_OK) == 0)
				break ;
			free(exec);
		}
	}
	return exec;
}

int cmd_exec(t_data *d_env, char *cmd)
{
	char **args = ft_split(cmd, " ");

	if(cmdlexer(cmd, d_env) != -1)
		return 0;
	pid_t	pid;
	pid = fork();
	if (pid < 0)
		return errno;
	if (!pid)
		d_env->lastret = execve(get_path(cmd), &args[0], d_env->env);
	wait(&pid);
	return d_env->lastret;
}

int subshell(char *line, t_data *data)
{
    int ret;

    line = tokenize(ft_chdir(ft_chwc(ft_chdollar(ft_epur_str(ft_pgross_str(line))))));
    char **res = ft_split(line, "\1");
    ret = execute(res, data);
    exit(ret);
}