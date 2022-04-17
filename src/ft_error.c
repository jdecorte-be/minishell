/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 07:53:49 by lxu-wu            #+#    #+#             */
/*   Updated: 2021/12/22 13:51:35 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_error(int e)
{
	if (e == 1)
		write(2, "Error\n", 6);
	else if (e == 2)
		printf("Malloc Failed\n");
	else if (e == 3)
		perror("pipe");
	else if (e == 4)
		perror("fork");
	else if (e == 5)
		perror("opendir");
	else if (e == 6)
		perror("closedir");
	else if (e == 7)
		perror("readdir");
	else if (e == 8)
		perror("dup2");
	else if (e == 9)
		perror("open");
	else if (e == 12)
	{
		perror("execve");
		exit (127);
	}
	exit(EXIT_FAILURE);
}
