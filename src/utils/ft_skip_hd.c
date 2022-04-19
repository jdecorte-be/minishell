/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_hd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:46:26 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/07 20:47:12 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_skip_hd(char *line)
{
	size_t	i;

	i = ft_hd_exist(line);
	while (i--)
		g_data->hd = g_data->hd->next;
}
