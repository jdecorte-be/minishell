/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 09:59:42 by lxu-wu            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/12/28 22:35:09 by jdecorte         ###   ########.fr       */
=======
/*   Updated: 2021/12/08 15:12:54 by lxu-wu           ###   ########.fr       */
>>>>>>> 032fb06ca1b34baf2ead7a4078944cdeea5fcb34
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	i;
	size_t	len_s1;
	size_t	len_dst;

	if (!s1 || !s2)
		return (0);
	len_s1 = ft_strlen(s1);
	len_dst = len_s1 + ft_strlen(s2);
	dst = malloc(sizeof(*dst) * len_dst + 1);
	if (!dst)
		ft_error(2);
	i = -1;
	while (s1[++i])
		dst[i] = s1[i];
	i = -1;
	while (s2[++i])
		dst[len_s1 + i] = s2[i];
	dst[len_s1 + i] = '\0';
	return (dst);
}
