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

	printf("1\n");
	wc = 0;
	name = 0;
	if (!line)
		return (0);
	wc = ft_wcsearch(line);
	while (wc)
	{
		printf("wc = %s\n", wc->content);
		printf("wcwo = %s\n", ft_woquote(wc->content));
		ft_lstadd_back(&name, ft_lstnew(ft_wcfile(ft_woquote(wc->content))));
		printf("\n\n\n\n");
		wc = ft_next(wc);
	}
	if (!name)
		return (line);
	while (name)
	{
		printf("name = %s\n", name->content);
		name = name->next;
	}
	return (0);
}
