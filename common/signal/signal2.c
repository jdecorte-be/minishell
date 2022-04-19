/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 18:05:06 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/05/10 01:23:26 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	here_doc_sig1(int sig)
{
	(void)sig;
	g_data->hd_stop = 1;
}

void	here_doc_sig2(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	exit(0);
}

void	c_handler_2(int sig)
{
	(void) sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	exit(130);
}

void	d_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	exit(0);
}
