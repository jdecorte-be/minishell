#include "../../inc/minishell.h"

int	ft_hd_exist(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '(')
			ft_skip_p(line, &i);
		else if (ft_strchr("\'\"", line[i]))
			ft_skip_q(line, &i);
		else if (!ft_strncmp(line + i, "<< ", 2))
			return (1);
		else
			i++;
	}
	return (0);
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

void	ft_here_doc(t_token *data)
{
	t_list	*limiters;
	char	*str;
	int		fd[2];


	char *test;

	str = 0;
	limiters = ft_search_limiters(data->cmd);
	if (limiters)
	{
		if (pipe(fd) == -1)
			ft_error(3);
		while (limiters)
		{
			// printf("lssss\n");
			str = readline("> ");
			if (!limiters->next)
			{
				ft_putstr_fd(str, fd[1]);
				ft_putchar_fd('\n', fd[1]);
			}
			if (!ft_strcmp(str, limiters->content))
				limiters = ft_next(limiters);
		}
		close(fd[1]);
	}
	data->redirect.infd = fd[0];
}