/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_hd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte-be <jdecorte@proton.me>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:46:26 by jdecorte-be           #+#    #+#             */
/*   Updated: 2022/04/25 15:39:54 by jdecorte-be          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_skip_hd(char *line)
{
	size_t	i;

	i = ft_hd_exist(line);
	while (i--)
		g_data->hd = g_data->hd->next;
}
