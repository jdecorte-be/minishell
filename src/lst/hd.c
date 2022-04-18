#include "../../inc/minishell.h"

t_hd	*ft_hdnew(int fd)
{
	t_hd	*hd;

	hd = malloc(sizeof(t_hd));
	if (!hd)
		return (0);
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

