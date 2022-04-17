#include "../../inc/minishell.h"

t_list	*ft_wcsearch(char *line)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	c1;
	t_list	*wc;

	i = 0;
	end = 0;
	wc = 0;
	while (line[end])
	{
		c1 = 0;
		start = end;
		if (line[end] && ft_strchr("\"\'", line[end]))
			ft_creat_tab2(line, &end, 0, 1);
		else if (line[end] && !ft_isspace(line[end]) && !ft_strchr("\'\"&|", line[end]))
		{
			while (line[end] && !ft_isspace(line[end]))
			{
				if (line[end++] == '*')
				{
					c1 = 1;
				}
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
	while (wc_tab[i])
	{
		// printf("%s\n", file);
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
		else if (*file && wc_tab[i] && !wc_tab[i + 1] && ft_exist(file, len - 1) && !ft_strrcmp(file, wc_tab[i], len - 1) && ++i)
			while (*file)
				file++;
		else
			break ;
	}
	if (!wc_tab[i] && !*file)
		return (1);
	return (0);
}

t_list	*ft_readfile(char *wc, DIR *loc)
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
		printf("%s %d\n", file->d_name, ft_wcmatch(wc_tab, file->d_name));
		if (ft_wcmatch(wc_tab, file->d_name))
		{
			ft_lstadd_back(&match, ft_lstnew(file->d_name));
			// str = ft_merge(match);
			ft_lstclear(&match, 0);
			ft_lstadd_back(&match, ft_lstnew(str));
		}
		file = readdir(loc);
	}
	return (match);
}

char	*ft_wcfile(char *wc)
{
	struct dirent	*file;	
	DIR				*loc;
	char			path[PATH_MAX];
	t_list			*match;

	loc = opendir(getcwd(path, PATH_MAX));
	if (loc == 0)
		ft_error(5);
	match = ft_readfile(wc, loc);
	if (closedir(loc) == -1)
		ft_error(6);
	return (0);
}
