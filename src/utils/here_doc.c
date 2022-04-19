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

void	putin_hd(char *line, int *fd)
{
	char *str;

	close(fd[0]);
	while (1)//ft_strcmp(str, line))
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
	data->hd_stop = 1;
	str = 0;
	if (pipe(fd) == -1)
		ft_error(3);
	data->pid = fork();
	if(data->pid  == -1)
		exit(0);
	if(!data->pid)
	{
		// signal(SIGINT, c_handler_doc);
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
	// free(line);
	return (fd[0]);
}

// t_hd	*ft_hd_order(char *line, t_token *token)
// {

// }

// t_hd	*ft_sort_hd(t_hd *hd, char *line, t_token *token)
// {
// 	int		*tab;
// 	size_t	i;

// 	tab = ft_hd_to_tab(hd);
// 	hd = ft_hd_order(line, token);
// 	size_t	i;
// 	t_hd	*hd;

// 	i = 0;
// 	while (token)
// 	{

// 	}
// }

// t_hd	*ft_sort_hd(t_hd *hd, char *line, t_token *token)
// {
// 	int		*tab;
// 	t_hd	*sorted;
// 	t_token	*tmp;
// 	size_t	i;

// 	tmp = token;
// 	tab = ft_hd_to_tab(hd);
// 	free(hd);
// 	hd = 0;
// 	sorted = ft_hd_order(line, tmp);
// 	i = 0;
// 	while (sorted)
// 	{
// 		i = sorted->fd - 1;
// 		ft_lstadd_back(&hd, tab[i]);
// 		sorted = sorted->next;
// 	}
// 	return (hd);
// }

t_hd	*ft_hd_finder(char *line)
{
	size_t	end;
	size_t	start;
	t_hd	*hd;
	int		hd_fd;
	
	end = 0;
	hd = 0;
	while (line[end])
	{
		if (line[end] == '(')
			ft_skip_p(line, &end);
		else if (ft_strchr("\'\"", line[end]))
			ft_skip_q(line, &end);
		else if (!ft_strncmp(line + end, "<< ", 2))
		{
			end = ft_next_word(line, end);
			start = end;
			while (line[end] && !ft_isspace(line[end]))
				end++;
			hd_fd = (ft_here_doc(ft_substr(line, start, end - start)));
			if (hd_fd > -1)
				ft_hdadd_back(&hd, ft_hdnew(hd_fd));
		}
		else
			end++;
	}
	// hd = ft_sort_hd(hd, line);
	return (hd);
}

void	ft_skip_hd(char *line)
{
	size_t	i;

	i = ft_hd_exist(line);
	// printf("%zu\n", i);
	while (i--)
		data->hd = data->hd->next;
}
