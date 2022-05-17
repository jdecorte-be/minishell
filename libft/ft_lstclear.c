/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte-be <jdecorte@proton.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 21:37:58 by jdecorte-be            #+#    #+#             */
/*   Updated: 2021/12/22 16:25:24 by jdecorte-be           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*elem_to_del;
	t_list	*tmp;

	if (lst && del)
	{
		elem_to_del = *lst;
		while (elem_to_del)
		{
			tmp = elem_to_del->next;
			del(elem_to_del->content);
			free(elem_to_del);
			elem_to_del = tmp;
		}
		*lst = NULL;
	}
}
