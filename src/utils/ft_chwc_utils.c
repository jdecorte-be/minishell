#include "../../inc/minishell.h"

t_list	*ft_wcsearch(char *line)
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
		c = 0;
		c1 = 0;
		start = end;
		if (line[end] && ft_strchr("\"\'", line[end]))
		{
			printf("1\n");
			ft_creat_tab2(line, &end, 0, 1);
		}
		if (line[end] && !ft_isspace(line[end]) && !ft_strchr("\'\"&|", line[end]))
		{
			while (line[end] && !ft_isspace(line[end]))
			{
				printf("2\n");
				if (line[end] && ft_strchr("\"\'", line[end]))
					ft_creat_tab2(line, &end, 0, 1);
				if (line[end] && line[end] == '*' && ++end)
					c1 = 1;
				else if (line[end])
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

int	ft_wcmatch(char **wc_tab, char *file)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (wc_tab[0][0] != '.' && *file == '.')
		return (0);
	while (wc_tab[i])
	{
		len = ft_strlen(wc_tab[i]);
		if (wc_tab[i] && *(wc_tab[i]) == '*' && ++i)
		{
			len = ft_strlen(wc_tab[i]);
			if (wc_tab[i])
				while (*file && ft_exist(file, len - 1) && ft_strncmp(file, wc_tab[i], len - 1))
					file++;
			else
				while (*file)
					file++;
		}
		else if (*file && wc_tab[i] && wc_tab[i + 1] && ft_exist(file, len - 1) && !ft_strncmp(file, wc_tab[i], len - 1) && ++i)
			file += len;
		else if (*file && wc_tab[i] && !wc_tab[i + 1] && ft_exist(file, len - 1) && !ft_strrcmp(file, wc_tab[i], len) && ++i)
			while (*file)
				file++;
		else
			break ;
	}
	if (!wc_tab[i] && !*file)
		return (1);
	return (0);
}

char	*ft_readfile(char *wc, DIR *loc)
{
	struct dirent	*file;
	char			**wc_tab;
	t_list			*match;
	char			*str;
	size_t			i;

	match = 0;
	wc_tab = ft_split4(wc, "*");
	i = 0;
	file = readdir(loc);
	while (file)
	{
		if (ft_wcmatch(wc_tab, file->d_name))
			ft_lstadd_back(&match, ft_lstnew(ft_strdup(file->d_name)));
			// ft_lstadd_back(&match, ft_lstnew(ft_trijoin("\'", file->d_name, "\'")));
		file = readdir(loc);
	}
	str = ft_lstmerge(match);
	ft_free_tab(wc_tab);
	ft_lstclear(&match, free);
	return (str);
}

char	*ft_wcfile(char *wc)
{
	DIR				*loc;
	char			path[PATH_MAX];
	char			*match;

	loc = opendir(getcwd(path, PATH_MAX));
	if (loc == 0)
		ft_error(5);
	match = ft_readfile(wc, loc);
	if (closedir(loc) == -1)
		ft_error(6);
	return (match);
}
