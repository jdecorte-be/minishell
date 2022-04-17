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
	printf("line = %s\n", line);
	wc = ft_wcsearch(line);
	while (wc)
	{
		ft_lstadd_back(&name, ft_lstnew(ft_wcfile(wc->content)));
		wc = ft_next(wc);
	}
	if (!name)
		return (line);
	while (wc)
	{
		printf("wc = %s\n", wc->content);
		wc = wc->next;
	}
	// ft_pgross_str(str);
	// loc = 
	// len = ft_chwc_len(line);
	return (0);
}