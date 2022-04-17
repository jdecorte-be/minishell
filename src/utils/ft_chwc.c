#include "../../inc/minishell.h"


char	*ft_chwc_str(char *line, t_list *name, t_list *wc, t_list *woq)
{
	size_t	start;
	size_t	end;
	char	*str;
	size_t	len;
	size_t	i;

	end = 0;
	str = 0;
	while (line[end])
	{
		start = end;
		if (wc)
		{
			len = ft_strlen(wc->content);
			if (line[end] && ft_exist(line + end, len - 1) && !ft_strncmp(line + end, wc->content, len -1))
			{
				i = 0;
				while (((char *)(wc->content))[i] && ++i)
					end++;
				if (name->content)
					str = ft_strjoin1(str, name->content);
				else
					str = ft_strjoin1(str, woq->content);
				woq = ft_next(woq);
				wc = ft_next(wc);
				name = ft_next(name);
			}
			else
			{
				while (line[end] && ft_exist(line + end, len - 1) && ft_strncmp(line + end, wc->content, len -1))
					end++;
				str = ft_strjoin3(str, ft_substr(line, start, end - start));
			}
		}
		else
		{
			while (line[end])
				end++;
			str = ft_strjoin3(str, ft_substr(line, start, end - start));
		}
	}
	return (str);
}

char	*ft_chwc2(char *line)
{
	char	*str;
	t_list	*woq;
	t_list	*name;
	t_list	*wc;
	t_tmp	tmp;

	tmp.i = 0;
	if (ft_strchr(line, '/'))
	{
		tmp.tab = ft_split4(line, "/");
		if (tmp.tab[tmp.i])
		{
			if (!tmp.i && ft_strchr(tmp.tab[tmp.i], '*'))
			{
				line += ft_strlen(tmp.tab[tmp.i]);
				if (tmp[1] && tmp[2])
					tmp.str = ft_wcfile(tmp.tab[0], getcwd(tmp.path, PATH_MAX), 2, line);
				else if (tmp.tab[1] && ft_strchr(tmp.tab[1], '/'))
				{
					printf("1\n");
					tmp.str = ft_wcfile(tmp.tab[0], getcwd(tmp.path, PATH_MAX), 1, line);
				}
				else
				{
					tmp.str = ft_wcfile(tmp.tab[0], getcwd(tmp.path, PATH_MAX), 0, 0);
				}
			}
		}
		line += 1;
		printf("line = %s\n", tmp.str);
		return (tmp.str);
	}
	return (ft_wcfile(line, getcwd(tmp.path, PATH_MAX), 0, 0));
}

char	*ft_chwc(char *line)
{
	char	*str;
	t_list	*woq;
	t_list	*name;
	t_list	*wc;
	t_tmp	tmp;

	woq = 0;
	wc = 0;
	name = 0;
	if (!line)
		return (0);
	wc = ft_wcsearch(line);
	tmp.lst = wc;
	while (tmp.lst)
	{
		ft_lstadd_back(&name, ft_lstnew(ft_chwc2((tmp.lst)->content)));
		tmp.lst = (tmp.lst)->next;
	}
	tmp.lst = wc;
	while (tmp.lst)
	{
		ft_lstadd_back(&woq, ft_lstnew(ft_woquote((tmp.lst)->content)));
		tmp.lst = (tmp.lst)->next;
	}
	if (!name)
		return (line);
	str = ft_chwc_str(line, name, wc, woq);
	free(line);
	return (str);
}
