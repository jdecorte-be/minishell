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
	return (lst);
}