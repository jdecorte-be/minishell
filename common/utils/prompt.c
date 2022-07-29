/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:33:36 by lyaiche           #+#    #+#             */
/*   Updated: 2022/05/09 19:35:16 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*prompt(void)
{
	char	*path;
	char	*line;
	char	*sub;
	int		i;

	path = NULL;
	path = getcwd(path, 1024);
	i = ft_strlen(path);
	while (path[i] != '/')
		i--;
	sub = ft_substr(path, i + 1, ft_strlen(path));
	line = ft_strjoin(sub, " ❯ ");
	free(path);
	free(sub);
	return (line);
}
