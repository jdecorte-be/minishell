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

		printf("%s== wc\n", wc->content);

	while (line[end])
	{
		// printf("%zu\n", end);
		start = end;
		if (wc)
		{
			// printf("1\n");
			len = ft_strlen(wc->content);
			if (line[end] && ft_exist(line + end, len - 1) && !ft_strncmp(line + end, wc->content, len -1))
			{
				// printf("2\n");
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
				// printf("cmp %d\n",ft_exist(line + end, len - 1));
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
	char	*pref;
	char	*suff;
	t_list	*match;
	t_list	*match2;
	void	*home;

	tmp.i = 0;
	tmp.tab = ft_split4(line, "/");
	while (tmp.tab[tmp.i] && !ft_strchr(tmp.tab[tmp.i], '*'))
		tmp.i++;
	if (tmp.tab[tmp.i])
		tmp.str = tmp.tab[tmp.i];
	printf("2\n");
	tmp.i2 = 0;
	tmp.tmp = 0;
	while (tmp.i2 < tmp.i)
		tmp.tmp = ft_strjoin1(tmp.tmp, tmp.tab[tmp.i2++]);
	printf("tmp.tmp %s\n", tmp.tmp);
	pref = tmp.tmp;
	tmp.i2 = tmp.i + 1;
	suff = 0;
	while (tmp.tab[tmp.i2])
		suff = ft_strjoin1(suff, tmp.tab[tmp.i2++]);
	printf("suff %s\n", suff);
	match = ft_wcfile(tmp.str, getcwd(tmp.path, PATH_MAX), 0, 0);
	tmp.lst = match;
	while (tmp.lst)
	{
		tmp.lst->content = ft_trijoin(pref, tmp.lst->content, suff);
		tmp.lst = tmp.lst->next;
	}
	tmp.lst = match;
	match2 = 0;
	home = getcwd(tmp.path, PATH_MAX);
	while (tmp.lst)
	{
		if (!access(ft_trijoin(home, "/", tmp.lst->content), F_OK))
			ft_lstadd_back(&match2, ft_lstnew(tmp.lst->content));
		tmp.lst = tmp.lst->next;
		printf("120\n");
	}



	// while ()
	// if (ft_strchr(line, '/'))
	// {
	// 	tmp.tab = ft_split4(line, "/");
	// 	if (tmp.tab[0])
	// 	{
	// 		if (!tmp.i && ft_strchr(tmp.tab[0], '*'))
	// 		{
	// 			if (tmp.tab[1] && tmp.tab[2])
	// 			{
	// 				tmp.str = ft_wcfile(tmp.tab[0], getcwd(tmp.path, PATH_MAX), 2, line + ft_strlen(tmp.tab[tmp.i]));
	// 				// tmp.str = ft_checkexist(tmp, line);
	// 			}
	// 			else if (tmp.tab[1] && ft_strchr(tmp.tab[1], '/'))
	// 			{
	// 				printf("1\n");
	// 				tmp.str = ft_wcfile(tmp.tab[0], getcwd(tmp.path, PATH_MAX), 1, line + ft_strlen(tmp.tab[tmp.i]));
	// 			}
	// 			else
	// 			{
	// 				tmp.str = ft_wcfile(tmp.tab[0], getcwd(tmp.path, PATH_MAX), 0, 0);
	// 			}
	// 		}
	// 	}
	// 	printf("line = %s\n", tmp.str);
	// 	return (tmp.str);
	// }
	// return (ft_wcfile(tmp.str, ft_strjoin(getcwd(tmp.path, PATH_MAX), "/"), 0, suff));
	return (ft_lstmerge(match2));
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
		printf("4\n");
		ft_lstadd_back(&name, ft_lstnew(ft_chwc2((tmp.lst)->content)));
		printf("1\n");
		tmp.lst = (tmp.lst)->next;
	}
	tmp.lst = wc;
	while (tmp.lst)
	{
		printf("2\n");
		ft_lstadd_back(&woq, ft_lstnew(ft_woquote((tmp.lst)->content)));
		printf("1\n");
		tmp.lst = (tmp.lst)->next;
	}
	printf("2\n");
	if (!name)
		return (line);
	str = ft_chwc_str(line, name, wc, woq);
	free(line);
	return (str);
}
