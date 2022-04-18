#include "../../inc/minishell.h"

int	ft_write_in_new_pipe(char *str)
{
	size_t	i;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_error(3);
	write(fd[1], str, ft_strlen(str));
	close(fd[1]);
	return (fd[0]);
}

int	ft_hd_replace(int fd)
{
	size_t	ret;
	size_t	i;
	char	*s1;
	char	*s2;

	s1 = 0;
	s2 = get_next_line(fd);
	while (s2)
	{
		s1 = ft_strjoin2(s1, s2);
		s2 = get_next_line(fd);
	}
	s2 = ft_chdollar_hd(s1);
	dup2(ft_write_in_new_pipe(s2), fd);
	return (fd);
}

void	ft_redirect_for_john(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (token->redirect.open && token->redirect.open->fd == 1)
		data->hd->fd = ft_hd_replace(data->hd->fd);
	token->redirect = ft_redirect(token->cmd, token->redirect, 0, 0);
	if (tmp->sub_token)
	{
		tmp = tmp->sub_token;
		while (tmp)
		{
			tmp->redirect = tmp->sup_token->redirect;
			tmp = tmp->next;
		}
	}
}
