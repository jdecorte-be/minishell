#include "../../inc/minishell.h"

size_t	ft_chwc_len(char *line)
{
	size_t	i;
	size_t	count;

	i = 0;
	return (i + count);
}

char	*ft_chwc_str(char *line, t_list *name, t_list *wc, t_list *woq)
{
	size_t	start;
	size_t	end;
	char	c1;
	char	*str;
	size_t	len;
	size_t	i;

	end = 0;
	str = 0;




	while (line[end])
	{
		// c1 = 0;
		// start = end;
		// if (line[end] && ft_strchr("\"\'", line[end]))
		// {
		// 	ft_creat_tab2(line, &end, 0, 1);
		// }
		// if (line[end] && !ft_isspace(line[end]) && !ft_strchr("\'\"&|", line[end]))
		// {
		// 	while (line[end] && !ft_isspace(line[end]))
		// 	{
		// 		if (line[end++] == '*')
		// 			c1 = 1;
		// 	}
		// }
		// else
		// 	while (line[end] && (ft_isspace(line[end]) || ft_strchr("&|", line[end])))
		// 		end++;
		// if (c1 == 0)
		// {
		// 	printf("1\n");
		// 	str = ft_strjoin(str, ft_substr(line, start, end - start));
		// }
		// else if (c1 == 1)
		// {
		// 	if (name->content)
		// 		str = ft_strjoin(str, name->content);
		// 	else
		// 		str = ft_strjoin(str, woq->content);
		// 	name = name->next;
		// 	woq = ft_next(woq);
		// }
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

char	*ft_chwc(char *line)
{
	char	*str;
	t_list	*woq;
	t_list	*name;
	t_list	*wc;
	t_list	*tmp;

	woq = 0;
	wc = 0;
	name = 0;

	if (!line)
		return (0);
	wc = ft_wcsearch(line);
	tmp = wc;
	while (tmp)
	{
		ft_lstadd_back(&name, ft_lstnew(ft_wcfile(tmp->content)));
		tmp = tmp->next;
	}
	tmp = wc;
	while (tmp)
	{
		ft_lstadd_back(&woq, ft_lstnew(ft_woquote(tmp->content)));
		tmp = tmp->next;
	}
	if (!name)
		return (line);
	// ft_lstclear(&name, free);
	// ft_lstclear(&woq, free);
	// ft_lstclear(&wc, free);
	str = ft_chwc_str(line, name, wc, woq);
	free(line);
	return (str);
}


				// if (c1 == 0)
				// 	str = ft_strjoin(str, ft_substr(line, start, end - start));
				// else if (c1 == 1)
				// {
				// 	str = ft_strjoin(str, name->content);
				// 	name = name->next;
				// }