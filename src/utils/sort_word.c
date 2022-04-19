/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:00:18 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/06 21:00:34 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_list	*ft_sort_word(t_list *lst)
{
	char	**tab;
	size_t	i;
	size_t	i2;
	char	*str;

	if (!lst)
		return (0);
	i2 = 0;
	i = 0;
	tab = ft_list_to_tab(lst);
	while (tab[i + 1])
	{
		if (tab[i][i2] > tab[i + 1][i2])
		{
			str = tab[i + 1];
			tab[i + 1] = tab[i];
			tab[i] = str;
			i = 0;
		}
		else if (tab[i][i2] == tab[i + 1][i2])
		{
			while (tab[i][i2] == tab[i + 1][i2])
				i2++;
			if (tab[i][i2] > tab[i + 1][i2])
			{
				str = tab[i + 1];
				tab[i + 1] = tab[i];
				tab[i] = str;
			}
			else
				i++;
			i2 = 0;
		}
		else
			i++;
	}
	lst = ft_tab_to_list(tab, lst);
	return (lst);
}
