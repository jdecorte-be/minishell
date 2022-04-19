/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:55:04 by lyaiche           #+#    #+#             */
/*   Updated: 2022/05/03 21:43:10 by jdecorte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		exit(ret);
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
	t_token	*token;

	line = ft_ecrase_p(line);
	if (ft_isprohibited(line) == 1)
	{
		free(line);
		exit (1);
	}
	line = ft_epur_str(((ft_chdir((ft_pgross_str((line)))))));
	token = ft_parsing(line);
	free(line);
	execute(token);
	ft_tokenclean_all(&token);
	return (g_data->lastret);
}

char	*access_path(char **allpath, char **s_cmd, int i)
{
	char	*path_part;
	char	*exec;

	path_part = ft_strjoin(allpath[i], "/");
	exec = ft_strjoin(path_part, s_cmd[0]);
	free(path_part);
	if (access(exec, F_OK | X_OK) == 0)
	{
		ft_free_tab(s_cmd);
		return (exec);
	}
	free(exec);
	return (NULL);
}

char	*get_path(char *cmd)
{
	int		i;
	char	**allpath;
	char	**s_cmd;
	char	*exec;

	i = -1;
	allpath = ft_split(my_getenv("PATH", NULL), ":");
	if (!allpath)
		return (cmd);
	s_cmd = ft_split2(cmd, " ");
	while (allpath[++i])
	{
		exec = access_path(allpath, s_cmd, i);
		if (access(exec, F_OK | X_OK) == 0)
			return (exec);
	}
	ft_free_tab(allpath);
	ft_free_tab(s_cmd);
	return (cmd);
}
