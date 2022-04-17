/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 21:37:58 by lxu-wu            #+#    #+#             */
/*   Updated: 2021/12/22 16:25:24 by lxu-wu           ###   ########.fr       */
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
