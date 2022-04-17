/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 21:39:17 by lxu-wu            #+#    #+#             */
/*   Updated: 2021/11/04 15:24:59 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmp;

	i = 0;
	while (n - i)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
		{
			tmp = (unsigned char *)(s + i);
			return (tmp);
		}
		i++;
	}
	return (0);
}
