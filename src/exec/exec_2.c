/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:55:04 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/17 20:36:58 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pipex(char *cmd)
{
	pid_t		pid;
	int			ret;
	int			p_fd[2];

	ret = 0;
	pipe(p_fd);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (!pid)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		ret = exec(cmd);
		ft_exit(ret);
	}
	else
	{
		close(p_fd[1]);
		dup2(p_fd[0], 0);
	}
	return (ret);
}

int	subshell(char *line)
{
	int		ret;
	t_token	*token;

	line = ft_epur_str(((ft_chdir((ft_pgross_str((line)))))));
	token = ft_parsing(line);
	free(line);
	execute(token);
	ft_tokenclean_all(&token);
	return (g_data->lastret);
}
