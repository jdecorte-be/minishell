/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:24:56 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/07 16:27:49 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**dont_exist(char **lastenv, int *index)
{
	char	**p;
	int		cnt;

	p = g_data->env;
	while (*p)
		p++;
	cnt = splitlen(g_data->env);
	p = ft_realloc(lastenv, sizeof(char *) * (cnt + 2));
	if (!p)
		return (NULL);
	if (lastenv != g_data->env)
		ft_memcpy(p, g_data->env, cnt * sizeof(char *));
	*index = cnt;
	g_data->env [cnt + 1] = NULL;
	return (p);
}

int	my_setenv(char *var, int e)
{
	int			offset;
	char		*c;
	static char	**lastenv;
	char		*name;
	char		*value;
	int			e_len;
	char		*tmp;

	if (e == 1)
	{
		e_len = egal_len(var);
		name = ft_substr(var, 0, e_len);
		if (var[e_len] == '=')
			value = ft_substr(var, e_len + 1, ft_strlen(var));
		else
			value = ft_strdup("\0");
		c = my_getenv(name, &offset);
		if (c)
		{
			if ((int)ft_strlen(c) >= ft_strlen(value))
			{
				tmp = value;
				while (*c && *value)
					*c++ = *value++;
				free(tmp);
				return (0);
			}
		}
		else
			lastenv = dont_exist(lastenv, &offset);
		g_data->env[offset]
			= ft_calloc(1, (size_t)((e_len + ft_strlen(value) + 2)));
		if (!(g_data->env[offset]))
			return (-1);
		c = g_data->env[offset];
		tmp = name;
		while ((*c && *name) && *c != '=')
		{
			*c = *name++;
			++c;
		}
		if (var[e_len] == '=')
			*c++ = '=';
		free(tmp);
	}
	else if (e == 2)
	{
		ft_free_tab(lastenv);
		lastenv = 0;
	}
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
