/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 07:53:49 by lxu-wu            #+#    #+#             */
/*   Updated: 2022/04/25 15:41:21 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	else if (e == 8)
		perror("dup2");
	else if (e == 9)
		perror("open");
	else if (e == 10)
		write(2, "using: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 45);
	else if (e == 11)
	{
		printf("using: \t./pipex <file1> <cmd1> <cmd2> ...");
		printf(" <cmdn> <file2>\n\t\tor\n");
		printf("\t./pipex here_doc <LIMITER> <file1> <cmd1> <cmd2> ...");
		printf(" <cmdn> <file2>\n");
	}
	else if (e == 12)
	{
		perror("execve");
	}
}
