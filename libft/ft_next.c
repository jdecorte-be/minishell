#include "libft.h"

t_list	*ft_next(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	lst = lst->next;
	free(tmp);
	return (lst);
}
