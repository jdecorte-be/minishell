/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte-be <jdecorte@proton.me>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:09:50 by jdecorte-be           #+#    #+#             */
/*   Updated: 2022/05/08 04:04:45 by jdecorte-be       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(int numerror)
{
	ft_free_tab(g_data->env);
	free(g_data);
	tcsetattr(0, TCSANOW, &g_data->new);
	exit(numerror);
}
