/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: decortejohn <decortejohn@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:25:22 by decortejohn       #+#    #+#             */
/*   Updated: 2022/01/26 16:06:25 by decortejohn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// int	mid_pipe(char *cmd)
// {
// 	int		p_fd[2];
// 	pid_t	pid;

// 	pipe(p_fd);
// 	pid = fork();
// 	if (pid < 0)
// 		return errno;
// 	if (!pid)
// 	{
// 		close(p_fd[0]);
// 		dup2(p_fd[1], 1);
// 		data->lastret = exec(cmd);
// 	}
// 	else
// 	{
// 		close(p_fd[1]);
// 		dup2(p_fd[0], 0);
// 		waitpid(pid, NULL, 0);

// 	}
// 	close(p_fd[1]);
// 	close(p_fd[0]);
// 	return data->lastret ;
// }

// int last_pipe(char *cmd)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid < 0)
// 		return errno;
// 	if (!pid)
// 		data->lastret = exec(cmd);
	
// 	dup2(data->stdin, 0);
// 	dup2(data->stdout, 0);
// 	wait(&pid);
// 	return data->lastret;
// }


// // puterror("$RES_REAL: ambiguous redirect\n");
// // printf("%d: %s\n", errno, input[i]);