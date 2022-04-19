/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:13:01 by lyaiche           #+#    #+#             */
/*   Updated: 2022/05/03 16:08:20 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_hd	*ft_hdnew(int fd)
{
	t_hd	*hd;

	hd = malloc(sizeof(t_hd));
	if (!hd)
		ft_error(2);
	hd->fd = fd;
	hd->next = NULL;
	return (hd);
}

t_hd	*ft_hdlast(t_hd *hd)
{
	t_hd	*last_elem;

	if (!hd)
		return (0);
	last_elem = hd;
	while (last_elem->next != 0)
		last_elem = last_elem->next;
	return (last_elem);
}

void	ft_hdadd_back(t_hd **hd, t_hd *new)
{
	t_hd	*last_elem;

	if (hd && new)
	{
		if (!*hd)
			*hd = new;
		else
		{
			last_elem = ft_hdlast(*hd);
			last_elem->next = new;
		}
	}
}

int	ft_hdsize(t_hd *hd)
{
	int		i;
	t_hd	*current;

	if (!hd)
		return (0);
	i = 1;
	current = hd;
	while (current->next != NULL)
	{
		i++;
		current = current->next;
	}
	return (i);
}

void	ft_clean_hd(t_hd *hd)
{
	t_hd	*tmp;

	while (hd)
	{
		tmp = hd;
		hd = hd->next;
		free(tmp);
	}
}
