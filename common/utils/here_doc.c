/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:55:45 by lyaiche           #+#    #+#             */
/*   Updated: 2022/05/03 16:06:52 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_hd_exist(char *line)
{
	size_t	i;
	size_t	n;

	n = 0;
	i = 0;
	while (line[i])
	{
		if (ft_strchr("\'\"", line[i]))
			ft_skip_q(line, &i);
		else if (!ft_strncmp(line + i, "<< ", 2) && ++i)
			n++;
		else
			i++;
	}
	return (n);
}

char	*ft_chlimiter(char *line, size_t *v)
{
	size_t	end;
	size_t	start;

	end = 0;
	end = ft_next_word(line, end);
	start = end;
	while (line[end] && !ft_isspace(line[end]))
		end++;
	*v = end;
	return (ft_substr(line, start, end - start));
}

t_list	*ft_search_limiters(char *line)
{
	t_list	*lst;
	size_t	i;
	size_t	v;

	v = 0;
	lst = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] && ft_strchr("\'\"", line[i]))
			ft_skip_q(line, &i);
		else if (line[i] && ft_strchr("(", line[i]))
			ft_skip_p(line, &i);
		else if (!ft_strncmp(line + i, "<< ", 2))
		{
			ft_lstadd_back(&lst, ft_lstnew(ft_chlimiter(line + i, &v)));
			i += v;
		}
		else
			i++;
	}
	return (lst);
}

void	putin_hd(char *line, int *fd)
{
	char	*str;

	signal(SIGINT, here_doc_sig2);
	close(fd[0]);
	while (1)
	{
		str = readline("> ");
		if (!str || !ft_strcmp(str, line))
			break ;
		ft_putstr_fd(str, fd[1]);
		ft_putchar_fd('\n', fd[1]);
	}
	close(fd[1]);
	exit(0);
}

int	ft_here_doc(char *line)
{
	int		fd[2];
	int		pid;

	signal(SIGINT, here_doc_sig1);
	if (pipe(fd) == -1)
		ft_error(3);
	pid = fork();
	if (pid == -1)
		ft_exit(0);
	if (!pid)
		putin_hd(line, fd);
	waitpid(pid, 0, 0);
	return (fd[0]);
}
