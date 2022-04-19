/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chwc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:41:40 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/22 17:05:35 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_list	*ft_wcsearch(char *line);

void	ft_wcmatch_2_1(t_tmp *tmp, char **wc_tab, char **file)
{
	free(tmp->str);
	tmp->str = ft_woquote(wc_tab[tmp->i]);
	tmp->len = ft_strlen(tmp->str);
	if (wc_tab[tmp->i])
	{
		while (**file && ft_exist(*file, tmp->len - 1)
			&& ft_strncmp(*file, tmp->str, tmp->len - 1))
			(*file)++;
	}
	else
	{
		while (**file)
			(*file)++;
	}
}

int	ft_wcmatch_2(t_tmp *tmp, char **wc_tab, char **file)
{
	tmp->str = ft_woquote(wc_tab[tmp->i]);
	tmp->len = ft_strlen(tmp->str);
	if (wc_tab[tmp->i] && *wc_tab[tmp->i] == '*' && ++tmp->i)
		ft_wcmatch_2(tmp, wc_tab, file);
	else if (**file && wc_tab[tmp->i] && wc_tab[tmp->i + 1]
		&& ft_exist(*file, tmp->len - 1)
		&& !ft_strncmp(*file, tmp->str, tmp->len - 1) && ++tmp->i)
	{
		*file += tmp->len;
	}
	else if (**file && wc_tab[tmp->i] && !wc_tab[tmp->i + 1]
		&& ft_exist(*file, tmp->len - 1)
		&& !ft_strrcmp(*file, tmp->str, tmp->len) && ++tmp->i)
	{
		while (**file)
			(*file)++;
	}
	else
	{
		free(tmp->str);
		return (1);
	}
	free(tmp->str);
	return (0);
}	

int	ft_wcmatch(char **wc_tab, char *file)
{
	t_tmp	tmp;

	tmp.i = 0;
	if (wc_tab[0][0] != '.' && *file == '.')
		return (0);
	while (wc_tab[tmp.i])
		if (ft_wcmatch_2(&tmp, wc_tab, &file))
			break ;
	if (!wc_tab[tmp.i] && !*file)
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
