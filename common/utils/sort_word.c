/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:00:18 by lyaiche           #+#    #+#             */
/*   Updated: 2022/05/03 16:03:41 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_sort_word_2(char **tab, int *i, int *i2, char *str)
{
	if (tab[*i][*i2] > tab[*i + 1][*i2])
	{
		str = tab[*i + 1];
		tab[*i + 1] = tab[*i];
		tab[*i] = str;
		*i = 0;
	}
	else if (tab[*i][*i2] == tab[*i + 1][*i2])
	{
		while (tab[*i][*i2] == tab[*i + 1][*i2])
			*i2 += 1;
		if (tab[*i][*i2] > tab[*i + 1][*i2])
		{
			str = tab[*i + 1];
			tab[*i + 1] = tab[*i];
			tab[*i] = str;
		}
		else
			*i += 1;
		*i2 = 0;
	}
	else
		*i += 1;
}

t_list	*ft_sort_word(t_list *lst)
{
	char	**tab;
	int		i;
	int		i2;
	char	*str;

	str = NULL;
	if (!lst)
		return (0);
	i2 = 0;
	i = 0;
	tab = ft_list_to_tab(lst);
	while (tab[i + 1])
		ft_sort_word_2(tab, &i, &i2, str);
	lst = ft_tab_to_list(tab, lst);
	return (lst);
}
