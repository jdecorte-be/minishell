#include "libft.h"

t_list	*ft_next(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return (0);
	tmp = lst;
	lst = lst->next;
	// free(tmp->content);
	// free(tmp);
	return (lst);
}
