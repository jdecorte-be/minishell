/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_chevron.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:49:25 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/17 20:23:19 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_cut_chevron(char *str)
{
	char	*tmp;
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
		{
			end = ft_next_word(str, ft_next_word(str, end));
			tmp = str;
			str = ft_cutoff(tmp, start, end - start);
			free(tmp);
			end -= end - start;
		}
		else
			end++;
	}
	return (str);
}
