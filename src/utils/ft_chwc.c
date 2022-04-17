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
	t_list	*file;
	t_list	*wc;

	if (!line)
		return (0);
	printf("line = %s\n", line);
	wc = ft_wcsearch(line);
	// file = ft_wcfile(wc);
	// if (!file)
	// 	return (line);
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