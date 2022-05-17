/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte-be <jdecorte@proton.me>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 09:59:21 by jdecorte-be            #+#    #+#             */
/*   Updated: 2021/12/23 19:44:16 by jdecorte-be           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*s2;

	if (!s1)
		return (0);
	size = ft_strlen(s1);
	s2 = malloc(sizeof(*s2) * size + 1);
	if (!s2)
		ft_error(2);
	ft_strlcpy(s2, s1, size + 1);
	return (s2);
}	
