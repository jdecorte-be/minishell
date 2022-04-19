/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:25:24 by decortejohn       #+#    #+#             */
/*   Updated: 2022/04/05 16:57:02 by jdecorte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int exec(char *cmd)
{
    char **s_cmd = ft_split2(ft_ecrase_q(cmd)," ");

    if(cmd[0] == '(')
       return subshell(ft_ecrase_p(cmd), data);
	else if(ft_strcmp(s_cmd[0], "echo") == 0)
        return echo(s_cmd);
    else if(ft_strcmp(s_cmd[0], "cd") == 0)
        return cd(s_cmd);
    else if(ft_strcmp(s_cmd[0], "pwd") == 0)
        return pwd();
    else if(ft_strcmp(s_cmd[0], "env") == 0)
        return print_env(data->env);
    else if(ft_strcmp(s_cmd[0], "export") == 0)
        return export(s_cmd);
    else if(ft_strcmp(s_cmd[0], "unset") == 0)
        return unset(s_cmd);
    else if(ft_strcmp(s_cmd[0], "exit") == 0)
        return exit_cmd(s_cmd);
	else
		return cmd_sys(ft_ecrase_p(cmd));
	return -1;
}

char *get_path(char *cmd)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(my_getenv("PATH", NULL), ":");
	s_cmd = ft_split2(cmd, " ");
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_tab(s_cmd);
			return (exec);
		}
		free(exec);
	}
	ft_free_tab(allpath);
	ft_free_tab(s_cmd);
	return (cmd);
}

int cmd_sys(char *cmd)
{
	char **args = ft_split2(cmd, " ");
	pid_t	pid;
	int		ret;
	size_t	i;
	
	i = 0 ;
	while (args[i])
	{
		args[i] = ft_ecrase_q(args[i]);
		i++;
	}
	pid = fork();
	if (pid < 0)
		perror("fork: ");
	if (!pid)
	{
		
		if(execve(get_path(cmd), &args[0], data->env) == -1)
		{
			puterror(ft_ecrase_q(args[0]), "command not found");
			exit (127);
		}
	}
	else
	{
		waitpid(pid, &ret, 0);
		kill(pid, SIGTERM);
	}
	return ret % 255;
}

int subshell(char *line, t_data *data)
{
    int ret;

    line = ft_epur_str(((ft_chdir((ft_pgross_str((line)))))));
	t_token *token = ft_parsing(line);
    execute(token);
	return data->lastret;
}

int	pipex(char *cmd)
{
	pid_t		pid;
	int			ret = 0;
	int			p_fd[2];

	pipe(p_fd);
	pid = fork();
	if (pid < 0)
		return -1;
	if (!pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		ret = exec(cmd);
		exit(ret);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
	}
	return ret;
}
