/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:24:56 by lyaiche           #+#    #+#             */
/*   Updated: 2022/05/08 19:17:57 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	end_setenv(char *c, char *name, char *value, int *offset)
{
	char	*tmp;

	tmp = name;
	c = (char *)name;
	while (*c && *c != '=')
		++c;
	(g_data->env)[*offset] = malloc((size_t)((int)(c - name) \
		+ ft_strlen(value) + 2));
	if (!((g_data->env)[*offset]))
		ft_exit(-1);
	c = (g_data->env)[*offset];
	while (*c && *name && *c != '=')
	{
		(*c = *name++);
		++c;
	}
	*c++ = '=';
	ft_strlcpy(c, value, ft_strlen(value) + 1);
	g_data->offset = *offset;
	free(tmp);
}

void	dont_exist(int *offset)
{
	static int	alloced;
	int			cnt;
	char		**p;

	p = g_data->env;
	cnt = splitlen(p);
	if (alloced)
	{
		g_data->env = (char **)ft_realloc((char *)g_data->env, \
			(size_t)(sizeof(char *) * (cnt + 2)));
		if (!g_data->env)
			ft_exit(-1);
	}
	else
	{
		alloced = 1;
		p = malloc((size_t)(sizeof(char *) * (cnt + 2)));
		if (!p)
			ft_exit(-1);
		ft_memmove(p, g_data->env, cnt * sizeof(char *));
		g_data->env = p;
	}
	(g_data->env)[cnt + 1] = NULL;
	*offset = cnt;
}

int	exist(char *var, char *value, char *name, char *c)
{
	char		*tmp;
	int			i;

	i = -1;
	if (var[egal_len(var)] != '=')
	{
		free(value);
		free(name);
		return (0);
	}
	tmp = value;
	if ((ft_strlen(c) >= ft_strlen(value)))
	{
		while (value[++i])
			(c[i] = value[i]);
		c[i] = '\0';
		free(tmp);
		free(name);
		return (0);
	}
	return (1);
}

int	my_setenv(char *var)
{
	char		*c;
	int			offset;
	char		*value;
	char		*name;

	name = ft_substr(var, 0, egal_len(var));
	if (var[egal_len(var)] == '=')
		value = ft_substr(var, egal_len(var) + 1, ft_strlen(var));
	else
		value = ft_strdup("");
	c = my_getenv(name, &offset);
	if (c)
	{
		if (exist(var, value, name, c) == 0)
			return (0);
	}
	else
		dont_exist(&offset);
	end_setenv(c, name, value, &offset);
	return (0);
}

char	*my_getenv(char *name, int *index)
{
	int		i;
	int		j;
	char	*sub;

	i = -1;
	while (g_data->env[++i])
	{
		j = 0;
		while (g_data->env[i][j] && g_data->env[i][j] != '=')
			j++;
		sub = ft_substr(g_data->env[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			if (index != NULL)
				*index = i;
			return (g_data->env[i] + j + 1);
		}
		free(sub);
	}
	return (NULL);
}
