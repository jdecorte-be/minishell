#include "../../inc/minishell.h"

size_t	ft_chwc_len(char *line)
{
	size_t	i;
	size_t	count;

	i = 0;
	return (i + count);
}

char	*ft_chwc(char *line)
{
	char	*str;
	char	*len;
	t_list	*name;
	t_list	*wc;

	wc = 0;
	name = 0;
	if (!line)
		return (0);
	wc = ft_wcsearch(line);
	while (wc)
	{
		ft_lstadd_back(&name, ft_lstnew(ft_wcfile(wc->content)));
		printf("\n\n\n\n");
		wc = ft_next(wc);
	}
	if (!name)
		return (line);
	int x = 0;
	while (name)
	{
		printf("name = %s\n", name->content);
		name = name->next;
	}
	return (0);
}