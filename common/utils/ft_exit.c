/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:09:50 by lyaiche           #+#    #+#             */
/*   Updated: 2022/05/03 17:32:43 by jdecorte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(int numerror)
{
	free(g_data);
	tcsetattr(0, TCSANOW, &g_data->new);
	exit(numerror);
}
