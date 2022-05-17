/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte-be <jdecorte@proton.me>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:56:34 by jdecorte-be        #+#    #+#             */
/*   Updated: 2022/05/08 18:04:10 by jdecorte-be       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ecraseq_tab(char *cmd)
{
	int		i;
	char	**tab;
	char	*tmp;

	tab = ft_split2(cmd, " ");
	i = -1;
	while (tab[++i])
	{
		tmp = tab[i];
		tab[i] = ft_ecrase_q(tab[i]);
		free(tmp);
	}
	return (tab);
}
