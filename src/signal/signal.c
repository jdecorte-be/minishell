/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:15:03 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/15 12:48:48 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	newprompt(int sig)
{
	printf("\n");
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
}

void	c_handler(int sig)
{
	newprompt(sig);
}

void	c_handler_fork(int sig)
{
	printf("^C\n");
	rl_on_new_line();
}

void	q_handler_fork(int sig)
{
	printf("^\\\n");
	rl_on_new_line();
}

void	c_handler_doc(int sig)
{
	kill(g_data->pid, SIGINT);
	newprompt(0);
}
