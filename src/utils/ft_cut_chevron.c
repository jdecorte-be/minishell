/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_chevron.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:49:25 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/19 19:19:21 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_cut_chevron2(char *str, size_t *end, size_t *start)
{
	char	*tmp;

	*end = ft_next_word(str, ft_next_word(str, *end));
	tmp = str;
	str = ft_cutoff(tmp, *start, *end - *start);
	free(tmp);
	(*end) -= ((*end) - (*start));
	return (str);
}

char	*ft_cut_chevron(char *str)
{
	size_t	start;
	size_t	end;

	if (!str)
		return (str);
	end = 0;
	while (str[end])
	{
		start = end;
		if (ft_strchr("\"\'", str[end]))
			ft_skip_q(str, &end);
		else if (str[end] == '(')
			ft_skip_p(str, &end);
		else if (ft_strchr("><", str[end]))
			str = ft_cut_chevron2(str, &end, &start);
		else
			end++;
	}
	return (str);
}
