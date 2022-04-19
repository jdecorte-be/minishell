/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:55:54 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/06 18:00:53 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (ptr == NULL)
		return (malloc(size));
	if (!size)
		return (ptr);
	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, size);
	return (new_ptr);
}

int	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i][egal_len(env[i])] == '=')
		{
			ft_putstr_fd(env[i], 1);
			ft_putstr_fd("\n", 1);
		}
		i++;
	}
	return (0);
}

void	format_env(char *var)
{
	char	*sub;
	char	*sub2;

	sub = ft_substr(var, 0, egal_len(var));
	printf("declare -x %s", sub);
	if (var[egal_len(var)] == '=')
	{
		sub2 = ft_substr(var, egal_len(var) + 1, ft_strlen(var));
		printf("=\"%s\"", sub2);
		free(sub2);
	}
	printf("\n");
	free(sub);
}

int	egal_len(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] != '=')
		i++;
	return (i);
}
