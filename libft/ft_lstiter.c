/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte-be <jdecorte@proton.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 21:38:15 by jdecorte-be            #+#    #+#             */
/*   Updated: 2021/10/04 21:38:16 by jdecorte-be           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*elem;

	if (lst && f)
	{
		elem = lst;
		while (elem)
		{
			f(elem->content);
			elem = elem->next;
		}
	}
}
