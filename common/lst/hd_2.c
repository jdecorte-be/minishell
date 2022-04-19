/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:53:58 by lyaiche           #+#    #+#             */
/*   Updated: 2022/05/02 13:18:04 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	*ft_hd_to_tab(t_hd *hd)
{
	size_t	i;
	size_t	size;
	int		*tab;
	t_hd	*tmp;

	i = 0;
	size = ft_hdsize(hd);
	tab = malloc(sizeof(tab) * size);
	if (!tab)
		ft_error(2);
	while (i < size)
	{
		tab[i++] = hd->fd;
		tmp = hd;
		hd = hd->next;
		free(tmp);
	}
	return (tab);
}
