/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:05:17 by lxu-wu            #+#    #+#             */
/*   Updated: 2021/12/18 20:50:36 by lxu-wu           ###   ########.fr       */
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
