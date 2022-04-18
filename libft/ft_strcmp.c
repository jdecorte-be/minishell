/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: decortejohn <decortejohn@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 07:53:16 by lxu-wu            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/01/29 18:20:08 by decortejohn      ###   ########.fr       */
=======
/*   Updated: 2022/01/29 22:05:28 by decortejohn      ###   ########.fr       */
>>>>>>> fe9aa9732eca25491461c7226333409f43befdf0
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;

	if (!s1)
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
