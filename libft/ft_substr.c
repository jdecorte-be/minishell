/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte-be <jdecorte@proton.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:05:17 by jdecorte-be            #+#    #+#             */
/*   Updated: 2021/12/22 14:02:40 by jdecorte-be           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dst;

	i = 0;
	if (!s)
		return (0);
	if (start + i < ft_strlen(s))
		while (s[start + i] && i < len)
			i++;
	dst = malloc(sizeof(*dst) * i + 1);
	if (!dst)
		ft_error(2);
	dst[i] = '\0';
	while (i--)
		dst[i] = s[start + i];
	return (dst);
}
