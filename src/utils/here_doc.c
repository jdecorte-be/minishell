/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:55:45 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/11 15:28:59 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	int		i;

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
	char	*str;
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

	close(fd[0]);
	while (1)
	{
		str = readline("> ");
		if (!str || !ft_strcmp(str, line))
			break ;
		ft_putstr_fd(str, fd[1]);
		ft_putchar_fd('\n', fd[1]);
	}
}

int	ft_here_doc(char *line)
{
	t_list	*limiters;
	char	*str;
	int		fd[2];

	g_data->hd_stop = 1;
	str = 0;
	if (pipe(fd) == -1)
		ft_error(3);
	g_data->pid = fork();
	if (g_data->pid == -1)
		ft_exit(0);
	if (!g_data->pid)
	{
		putin_hd(line, fd);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		printf("pepepeppepepe");
		wait(NULL);
		signal(SIGINT, c_handler);
	}
	signal(SIGINT, c_handler);
	return (fd[0]);
}
