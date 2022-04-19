/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:25:24 by decortejohn       #+#    #+#             */
/*   Updated: 2022/05/10 18:53:59 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	lexer(char **s_cmd, char *cmd)
{
	if (cmd[0] == '(')
		return (subshell(cmd));
	else if (ft_strcmp(s_cmd[0], "echo") == 0)
		return (echo(s_cmd));
	else if (ft_strcmp(s_cmd[0], "cd") == 0)
		return (cd(cmd));
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

int	exec(char *cmd)
{
	char	**s_cmd;
	int		ret;
	char	*tmp;

	ret = 0;
	tmp = ft_ecrase_q(cmd);
	s_cmd = ft_split2(tmp, " ");
	ret = lexer(s_cmd, cmd);
	ft_free_tab(s_cmd);
	free(tmp);
	return (ret);
}

void	file_check(char *cmd, char *tmp)
{
	if (cmd[0] == '.' && !cmd[1])
	{
		puterror(tmp, "filename argument required");
		printf(".: usage: . filename [arguments]\n");
	}
	else if (access(cmd, F_OK) == 0 && !(cmd[0] == '.' && cmd[1] == '.'))
		puterror(tmp, "is a directory");
	else if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/')
		|| my_getenv("PATH", 0) == 0)
		puterror(tmp, "No such file or directory");
	else
		puterror(tmp, "command not found");
}

void	not_pid(char *cmd, char **args)
{
	char	*tmp;

	signal(SIGINT, c_handler_2);
	signal(SIGQUIT, q_handler);
	signal(SIGKILL, d_handler);
	if (execve(get_path(cmd), &args[0], g_data->env) == -1)
	{
		tmp = ft_ecrase_q(args[0]);
		file_check(cmd, tmp);
		ft_free_tab(args);
		free(tmp);
		free(cmd);
		exit(127);
	}
}

int	cmd_sys(char *cmd)
{
	char	**args;
	pid_t	pid;
	int		ret;

	ret = 0;
	pid = 0;
	args = ecraseq_tab(cmd);
	pid = fork();
	if (pid < 0)
	{
		perror("fork: ");
		ft_exit(1);
	}
	if (!pid)
		not_pid(cmd, args);
	free(cmd);
	ft_free_tab(args);
	waitpid(pid, &ret, 0);
	kill(pid, SIGKILL);
	signal(SIGINT, c_handler);
	signal(SIGQUIT, SIG_IGN);
	return (ret % 255);
}
