#include "../../inc/minishell.h"

t_list	*ft_wcsearch2(char *line)
{
	size_t	start;
	size_t	end;
	char	c1;
	t_list	*wc;
	char	c;

	end = 0;
	wc = 0;
	while (line[end])
	{
		c1 = 0;
		if (line[end] && line[end] == '(')
			ft_skip_p(line, &end);
		else if (line[end] && !ft_isspace(line[end]) && line[end] != '(')
		{
			start = end;
			while (line[end] && !ft_isspace(line[end]) && line[end] != '(')
			{
				// printf("1\n");
				if (ft_strchr("\'\"", line[end]))
					ft_skip_q(line, &end);
				else if (line[end] == '*' && ++end)
					c1 = 1;
				else
					end++;
			}
			if (c1 == 1)
				ft_lstadd_back(&wc, ft_lstnew(ft_substr(line, start, end - start)));
		}
		else
			end++;
		
	}
	return (wc);
}

int	ft_chwc_ok2(char *line)
{
	size_t	i;
	char	c;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (ft_strchr("\"\'", line[i]))
			ft_skip_q(line, &i);
		else if (line[i] == '(')
			ft_skip_p(line, &i);
		else if (line[i] == '*')
			return (0);
		else
			i++;
	}
	return (1);
}

char	*ft_transf(char *line)
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
	// printf("2\n");
	tmp.i2 = 0;
	tmp.tmp = 0;
	while (tmp.i2 < tmp.i)
		tmp.tmp = ft_strjoin1(tmp.tmp, tmp.tab[tmp.i2++]);
	// printf("tmp.tmp %s\n", tmp.tmp);
	pref = tmp.tmp;
	tmp.i2 = tmp.i + 1;
	suff = 0;
	while (tmp.tab[tmp.i2])
		suff = ft_strjoin1(suff, tmp.tab[tmp.i2++]);
	// printf("suff %s\n", suff);
	match = ft_wcfile(tmp.str, getcwd(tmp.path, PATH_MAX), 0, 0);
	if (ft_lstsize(match) > 1)
	{
		printf("pas bien trop grand\n");
		return (0);
	}
	tmp.lst = match;
	tmp.lst->content = ft_trijoin(pref, tmp.lst->content, suff);
	match2 = 0;
	if (!access(tmp.lst->content, F_OK))
		ft_lstadd_back(&match2, ft_lstnew(tmp.lst->content));
	else if (!access(ft_trijoin(home, "/", tmp.lst->content), F_OK))
		ft_lstadd_back(&match2, ft_lstnew(tmp.lst->content));
	return (ft_lstmerge(match2));
}

char	*ft_redirect_chwc(char *line)
{
	size_t	i;
	char	*str;
	t_list	*wc;
	t_list	*name;
	t_list	*tmp;
	t_list	*woq;

	if (!line)
		return (0);
	if (ft_chwc_ok2(line))
		return (line);
	wc = ft_wcsearch2(line);
	// printf("1\n");
	name = 0;
	tmp = wc;
	while (tmp)
	{
		ft_lstadd_back(&name, ft_lstnew(ft_transf(ft_ecrase_q(tmp->content))));
		tmp = tmp->next;	
	}
	tmp = wc;
	while (tmp)
	{
		// printf("2\n");
		ft_lstadd_back(&woq, ft_lstnew(ft_woquote((tmp)->content)));
		// printf("1\n");
		tmp = (tmp)->next;
	}
	// printf("2\n");
	if (!name)
		return (line);
	str = ft_chwc_str(line, name, wc, woq);
	free(line);
	return (str);
	
}