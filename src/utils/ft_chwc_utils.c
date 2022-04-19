/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chwc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:41:40 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/06 20:46:38 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_list	*ft_wcsearch(char *line)
{
	size_t	start;
	size_t	end;
	char	c1;
	t_list	*wc;

	end = 0;
	wc = 0;
	while (line[end])
	{
		c1 = 0;
		start = end;
		if (line[end] && ft_strchr("<>", line[end]))
			end = ft_next_word(line, ft_next_word(line, end));
		else if (line[end] && !ft_isspace(line[end])
			&& !ft_strchr("&|", line[end]))
		{
			while (line[end] && !ft_isspace(line[end]))
			{
				if (line[end] && ft_strchr("\"\'", line[end]))
					ft_skip_q(line, &end);
				else if (line[end] && line[end] == '*' && ++end)
					c1 = 1;
				else if (line[end])
					end++;
			}
			if (c1 == 1)
				ft_lstadd_back(&wc, ft_lstnew
					(ft_substr(line, start, end - start)));
		}
		else if (line[end])
			end++;
	}
	return (wc);
}

int	ft_wcmatch(char **wc_tab, char *file)
{
	size_t	i;
	size_t	len;
	char	*woq;

	i = 0;
	if (wc_tab[0][0] != '.' && *file == '.')
		return (0);
	while (wc_tab[i])
	{
		woq = ft_woquote(wc_tab[i]);
		len = ft_strlen(woq);
		if (wc_tab[i] && *wc_tab[i] == '*' && ++i)
		{
			free(woq);
			woq = ft_woquote(wc_tab[i]);
			len = ft_strlen(woq);
			if (wc_tab[i])
			{
				while (*file && ft_exist(file, len - 1)
					&& ft_strncmp(file, woq, len - 1))
					file++;
			}
			else
			{
				while (*file)
					file++;
			}
		}
		else if (*file && wc_tab[i] && wc_tab[i + 1] && ft_exist(file, len - 1)
			&& !ft_strncmp(file, woq, len - 1) && ++i)
		{
			file += len;
		}
		else if (*file && wc_tab[i] && !wc_tab[i + 1]
			&& ft_exist(file, len - 1) && !ft_strrcmp(file, woq, len) && ++i)
		{
			while (*file)
				file++;
		}
		else
		{
			free(woq);
			break ;
		}
		free(woq);
	}
	if (!wc_tab[i] && !*file)
		return (1);
	return (0);
}

t_list	*ft_readfile(char *wc, DIR *loc, char mode, char *add)
{
	struct dirent	*file;
	char			**wc_tab;
	t_list			*match;
	size_t			i;

	(void)mode;
	(void)add;
	match = 0;
	wc_tab = ft_split4(wc, "*");
	i = 0;
	file = readdir(loc);
	while (file)
	{
		if (ft_wcmatch(wc_tab, file->d_name))
			ft_lstadd_back(&match, ft_lstnew(ft_strdup(file->d_name)));
		file = readdir(loc);
	}
	ft_free_tab(wc_tab);
	ft_sort_word(match);
	return (match);
}

t_list	*ft_wcfile(char *wc, char *path, char mode, char *add)
{
	DIR				*loc;
	t_list			*match;

	loc = opendir(path);
	if (loc == 0)
		ft_error(5);
	match = ft_readfile(wc, loc, mode, add);
	if (closedir(loc) == -1)
		ft_error(6);
	return (match);
}
