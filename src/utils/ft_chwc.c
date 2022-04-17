#include "../../inc/minishell.h"

size_t	ft_chwc_len(char *line)
{
	size_t	i;
	size_t	count;

	i = 0;
	return (i + count);
}

char	*ft_chwc_str(char *line, t_list *name, t_list *wc)
{
	size_t	start;
	size_t	end;
	char	c1;
	char	*str;

	end = 0;
	wc = 0;
	str = 0;
	while (line[end])
	{
		c1 = 0;
		start = end;
		if (line[end] && ft_strchr("\"\'", line[end]))
		{
			ft_creat_tab2(line, &end, 0, 1);
		}
		else if (line[end] && !ft_isspace(line[end]) && !ft_strchr("\'\"&|", line[end]))
		{
			while (line[end] && !ft_isspace(line[end]))
			{
				if (line[end++] == '*')
					c1 = 1;
			}
		}
		else
			while (line[end] && (ft_isspace(line[end]) || ft_strchr("&|", line[end])))
				end++;
		printf("c == %d\n", c1);
		if (c1 == 0)
			str = ft_strjoin(str, ft_substr(line, start, end - start));
		else if (c1 == 1)
		{
			str = ft_strjoin(str, name->content);
			name = name->next;
		}
	}
	return (str);
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
		printf("wc = %s\n", wc->content);
		printf("wcwo = %s\n", ft_woquote(wc->content));
		ft_lstadd_back(&name, ft_lstnew(ft_wcfile(ft_woquote(wc->content))));
		printf("\n\n\n\n");
		wc = ft_next(wc);
	}
	if (!name)
		return (line);

	t_list *tmp;

	tmp = name;	
	while (tmp)
	{
		printf("name = %s|\n", tmp->content);
		tmp = tmp->next;
	}

	str = ft_chwc_str(line, name, wc);
	printf("string = %s\n", str);
	return (0);
}


				// if (c1 == 0)
				// 	str = ft_strjoin(str, ft_substr(line, start, end - start));
				// else if (c1 == 1)
				// {
				// 	str = ft_strjoin(str, name->content);
				// 	name = name->next;
				// }