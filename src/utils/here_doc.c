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
		else if (!ft_strncmp(line + i, "<< ", 2))
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
	return (ft_substr(line, start, end - start));//remplacer le 0 par start; et end par end - start;
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

int	ft_here_doc(char *line)
{
	t_list	*limiters;
	char	*str;
	int		fd[2];

	// printf("line == %s\n", line);
	str = 0;
	if (pipe(fd) == -1)
		ft_error(3);
	// limiters = ft_search_limiters(line);
	while (ft_strcmp(str, line))
	{
		// printf("salsal\n");
		// printf("lssss\n");
		str = readline("> ");
		if (!str)
			break ;
		ft_putstr_fd(str, fd[1]);
		ft_putchar_fd('\n', fd[1]);
	}
	free(line);
	close(fd[1]);
	return (fd[0]);
}

t_hd	*ft_hd_finder(char *line)
{
	size_t	end;
	size_t	start;
	t_hd	*hd;
	
	end = 0;
	hd = 0;
	while (line[end])
	{
		if (ft_strchr("\'\"", line[end]))
			ft_skip_q(line, &end);
		else if (!ft_strncmp(line + end, "<< ", 2))
		{
			end = ft_next_word(line, end);
			start = end;
			while (line[end] && !ft_isspace(line[end]))
				end++;
			ft_hdadd_back(&hd, ft_hdnew((ft_here_doc(ft_substr(line, start, end - start)))));
		}
		else
			end++;
	}
	return (hd);
}