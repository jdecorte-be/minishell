/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trijoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 07:53:59 by lxu-wu            #+#    #+#             */
/*   Updated: 2021/12/22 22:24:16 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_trijoin(char const *s1, char const *s2, char const *s3)
{
	char	*dst;
	size_t	i;
	size_t	cur_len;
	size_t	len_dst;

	len_dst = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	dst = malloc(sizeof(*dst) * len_dst + 1);
	if (!dst)
		return (0);
	i = -1;
	if (s1)
		while (s1[++i])
			dst[i] = s1[i];
	free((void *)s1);
	cur_len = i;
	if (!s1)
		cur_len = 0;
	i = -1;
	if (s2)
		while (s2[++i])
			dst[cur_len + i] = s2[i];
	cur_len += i;
	i = -1;
	if (s3)
		while (s3[++i])
			dst[cur_len + i] = s3[i];
	dst[cur_len + i] = '\0';
	return (dst);
}
