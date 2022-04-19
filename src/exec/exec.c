/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:25:24 by decortejohn       #+#    #+#             */
/*   Updated: 2022/04/16 14:57:12 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec(char *cmd)
{
	char	**s_cmd;

	s_cmd = ft_split2(ft_ecrase_q(cmd), " ");
	if (cmd[0] == '(')
		return (subshell(ft_ecrase_p(cmd)));
	else if (ft_strcmp(s_cmd[0], "echo") == 0)
		return (echo(s_cmd));
	else if (ft_strcmp(s_cmd[0], "cd") == 0)
		return (cd(s_cmd));
	else if (ft_strcmp(s_cmd[0], "pwd") == 0)
		return (pwd());
	else if (ft_strcmp(s_cmd[0], "env") == 0)
		return (print_env(g_data->env));
	else if (ft_strcmp(s_cmd[0], "export") == 0)
		return (export(s_cmd));
	else if (ft_strcmp(s_cmd[0], "unset") == 0)
		return (unset(s_cmd));
	else if (ft_strcmp(s_cmd[0], "exit") == 0)
		exit_cmd(s_cmd);
	else
		return (cmd_sys(ft_ecrase_p(cmd)));
	return (-1);
}

char	*get_path(char *cmd)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(my_getenv("PATH", NULL), ":");
	s_cmd = ft_split2(cmd, " ");
	if (!allpath)
		return (cmd);
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

void	sig(pid_t pid, int ret)
{
	waitpid(pid, &ret, 0);
	kill(pid, SIGTERM);
	signal(SIGINT, c_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	not_pid(char *cmd, char **args)
{
	if (execve(get_path(cmd), &args[0], g_data->env) == -1)
	{
		puterror(ft_ecrase_q(args[0]), "command not found");
		ft_free_tab(args);
		ft_exit(127);
	}
}

int	cmd_sys(char *cmd)
{
	char	**args;
	pid_t	pid;
	int		ret;
	size_t	i;

	i = 0 ;
	args = ft_split2(cmd, " ");
	while (args[i])
	{
		args[i] = ft_ecrase_q(args[i]);
		i++;
	}
	pid = fork();
	signal(SIGINT, c_handler_fork);
	signal(SIGQUIT, q_handler_fork);
	if (pid < 0)
		perror("fork: ");
	if (!pid)
		not_pid(cmd, args);
	else
	{
		ft_free_tab(args);
		sig(pid, ret);
	}
	return (ret % 255);
}
