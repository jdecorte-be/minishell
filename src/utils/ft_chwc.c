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

	return (ft_wcfile(line));
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
	tmp.tmp = wc;
	while (tmp.tmp)
	{
		ft_lstadd_back(&name, ft_lstnew(ft_chwc2((tmp.tmp)->content)));
		tmp.tmp = (tmp.tmp)->next;
	}
	tmp.tmp = wc;
	while (tmp.tmp)
	{
		ft_lstadd_back(&woq, ft_lstnew(ft_woquote((tmp.tmp)->content)));
		tmp.tmp = (tmp.tmp)->next;
	}
	if (!name)
		return (line);
	str = ft_chwc_str(line, name, wc, woq);
	free(line);
	return (str);
}
