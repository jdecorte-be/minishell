/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte-be <jdecorte@proton.me>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:33:36 by jdecorte-be           #+#    #+#             */
/*   Updated: 2022/05/09 19:35:16 by jdecorte-be          ###   ########.fr       */
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
