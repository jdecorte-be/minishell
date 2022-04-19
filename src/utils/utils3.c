/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:01:36 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/06 21:01:42 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**ft_list_to_tab(t_list *lst)
{
	char	**tab;
	size_t	i;

	tab = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!tab)
		ft_error(2);
	i = 0;
	while (lst)
	{
		tab[i++] = lst->content;
		lst = lst->next;
	}
	tab[i] = 0;
	return (tab);
}

t_list	*ft_tab_to_list(char **tab, t_list *lst)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		lst->content = tab[i++];
		lst = lst->next;
	}
	free(tab);
	return (lst);
}

t_token	*ft_tab_to_token(char **tab)
{
	size_t	i;
	t_token	*token;

	if (!tab || !*tab)
		return (0);
	token = 0;
	i = 0;
	while (tab[i])
	{
		ft_tokenadd_back(&token, ft_tokennew(tab[i++]));
	}
	free(tab);
	return (token);
}

t_token	*ft_tab_to_token2(char **tab, t_token *sup_token)
{
	size_t	i;
	t_token	*token;

	if (!tab || !*tab)
		return (0);
	token = 0;
	i = 0;
	while (tab[i])
	{
		ft_tokenadd_back(&token, ft_sub_tokennew(tab[i++], sup_token));
	}
	free(tab);
	return (token);
}
