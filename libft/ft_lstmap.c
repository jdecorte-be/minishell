/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte-be <jdecorte@proton.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 09:58:27 by jdecorte-be            #+#    #+#             */
/*   Updated: 2021/10/18 09:58:28 by jdecorte-be           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*tmps;

	if (!lst || !f)
		return (0);
	tmp = ft_lstnew(f(lst->content));
	if (!tmp)
		return (0);
	tmps = tmp;
	while (lst->next)
	{
		tmps->next = ft_lstnew(f(lst->next->content));
		if (!tmps)
		{
			ft_lstclear(&tmp, del);
			return (NULL);
		}
		tmps = tmps->next;
		lst = lst->next;
	}
	tmps->next = NULL;
	return (tmp);
}
