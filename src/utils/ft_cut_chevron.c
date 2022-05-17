/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_chevron.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte-be <jdecorte@proton.me>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:49:25 by jdecorte-be           #+#    #+#             */
/*   Updated: 2022/04/25 15:39:54 by jdecorte-be          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
