/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hd_finder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:28:35 by lyaiche           #+#    #+#             */
/*   Updated: 2022/05/08 02:23:26 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_hd_finder_2(char *line, size_t *start, size_t *end, t_hd **hd)
{
	int		hd_fd;

	*end = ft_next_word(line, *end);
	*start = *end;
	while (line[*end] && !ft_isspace(line[*end]))
		*end += 1;
	hd_fd = (ft_here_doc(ft_substr(line, *start, *end - *start)));
	if (hd_fd > -1)
		ft_hdadd_back(hd, ft_hdnew(hd_fd));
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
		if (line[end] == '(')
			ft_skip_p(line, &end);
		else if (ft_strchr("\'\"", line[end]))
			ft_skip_q(line, &end);
		else if (!ft_strncmp(line + end, "<< ", 2))
		{
			ft_hd_finder_2(line, &start, &end, &hd);
		}
		else
			end++;
	}
	return (hd);
}
