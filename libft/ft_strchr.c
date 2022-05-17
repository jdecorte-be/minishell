/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte-be <jdecorte@proton.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 21:41:36 by jdecorte-be            #+#    #+#             */
/*   Updated: 2021/12/29 04:05:44 by jdecorte-be           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s && *s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s && *s == (char)c)
		return ((char *)s);
	else
		return (0);
}
