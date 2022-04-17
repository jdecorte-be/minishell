/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:00:34 by lxu-wu            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/12/28 20:51:09 by jdecorte         ###   ########.fr       */
=======
/*   Updated: 2021/10/18 10:00:35 by lxu-wu           ###   ########.fr       */
>>>>>>> 032fb06ca1b34baf2ead7a4078944cdeea5fcb34
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		if ((((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
				|| (!s1[i] || !s2[i]))
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
