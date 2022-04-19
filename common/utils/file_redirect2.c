/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirect2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 18:27:43 by lxu-wu            #+#    #+#             */
/*   Updated: 2022/05/05 02:25:03 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_redirect_check_2(t_list **tmp, char *c)
{
	*c = ft_strstrchr((*tmp)->content, "|&()");
	if (*c != 0)
	{
		printf("boshell: syntax error near unexpected token `%c'\n", *c);
		return (0);
	}
	*tmp = (*tmp)->next;
	return (1);
}

int	ft_redirect_check(t_redirect file)
{
	t_list	*tmp;
	char	c;

	tmp = file.infile;
	while (tmp)
	{
		if (!ft_redirect_check_2(&tmp, &c))
			return (0);
	}
	tmp = file.outfile;
	while (tmp)
	{
		c = ft_strstrchr(tmp->content, "|&()");
		if (c != 0)
		{
			printf("boshell: syntax error near unexpected token `%c'\n", c);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	ft_chrredirect_2(t_hd **open, t_hd **open2, int i, int i2)
{
	if (i == 0)
		ft_hdadd_back(open2, ft_hdnew(1));
	else if (i != 0)
		ft_hdadd_back(open2, ft_hdnew(0));
	if (i2 == 0)
		ft_hdadd_back(open, ft_hdnew(1));
	else if (i2 != 0)
		ft_hdadd_back(open, ft_hdnew(0));
}

char	*ft_chrredirect(char *line, t_hd **open, t_hd **open2, size_t *v)
{
	size_t	end;
	size_t	start;
	int		i;
	int		i2;

	end = 0;
	i = 2;
	i2 = 2;
	if (line[end] == '<')
		while (line[end] == '<' && i2--)
			end++;
	else
		while (line[end] == '>' && i--)
			end++;
	ft_chrredirect_2(open, open2, i, i2);
	while (ft_isspace(line[end]))
		end++;
	start = end;
	while (line[end] && !ft_isspace(line[end]))
		end++;
	*v = end;

	return (ft_substr(line, start, end - start));
}
