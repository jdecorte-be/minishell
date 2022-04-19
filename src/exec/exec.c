/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:25:24 by decortejohn       #+#    #+#             */
/*   Updated: 2022/04/23 19:18:59 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec(char *cmd)
{
	char	**s_cmd;
	int		ret;

	s_cmd = ft_split2(ft_ecrase_q(cmd), " ");
	if (cmd[0] == '(')
		ret = (subshell(ft_ecrase_p(cmd)));
	else if (ft_strcmp(s_cmd[0], "echo") == 0)
		ret = (echo(s_cmd));
	else if (ft_strcmp(s_cmd[0], "cd") == 0)
		ret = (cd(s_cmd));
	else if (ft_strcmp(s_cmd[0], "pwd") == 0)
		ret = (pwd());
	else if (ft_strcmp(s_cmd[0], "env") == 0)
		ret = (print_env(g_data->env));
	else if (ft_strcmp(s_cmd[0], "export") == 0)
		ret = (export(s_cmd));
	else if (ft_strcmp(s_cmd[0], "unset") == 0)
		ret = (unset(s_cmd));
	else if (ft_strcmp(s_cmd[0], "exit") == 0)
		exit_cmd(s_cmd);
	else
		ret = (cmd_sys(ft_ecrase_p(cmd)));
	ft_free_tab(s_cmd);
	return (ret);
}

void	sig(pid_t *pid, int *ret)
{
	waitpid(*pid, ret, 0);
	kill(*pid, SIGTERM);
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
		sig(&pid, &ret);
	}
	return (ret % 255);
}
