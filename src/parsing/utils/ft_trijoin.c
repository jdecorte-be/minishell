/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trijoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: decortejohn <decortejohn@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 07:53:59 by lxu-wu            #+#    #+#             */
/*   Updated: 2022/01/23 17:04:57 by decortejohn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char	*ft_trijoin(char *s1, char *s2, char *s3)
{
	char	*dst;
	size_t	i;
	size_t	cur_len;
	size_t	len_dst;

	len_dst = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	dst = malloc(sizeof(*dst) * len_dst + 1);
	if (!dst)
		return (0);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			dst[i] = s1[i];
			i++;
		}
	}
	cur_len = i;
	if (!s1)
		cur_len = 0;
	i = 0;
	if (s2)
	{
		while (s2[i])
		{
			dst[cur_len + i] = s2[i];
			i++;
		}
	}
	cur_len += i;
	i = 0;
	if (s3)
	{
		while (s3[i])
		{
			dst[cur_len + i] = s3[i];
			i++;
		}
	}
	dst[cur_len + i] = '\0';
	return (dst);
}

char	*ft_trijoin1(char *s1, char *s2, char *s3)
{
	char	*dst;
	size_t	i;
	size_t	cur_len;
	size_t	len_dst;

	len_dst = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	dst = malloc(sizeof(*dst) * len_dst + 1);
	if (!dst)
		return (0);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			dst[i] = s1[i];
			i++;
		}
		free(s1);
	}
	cur_len = i;
	if (!s1)
		cur_len = 0;
	i = 0;
	if (s2)
	{
		while (s2[i])
		{
			dst[cur_len + i] = s2[i];
			i++;
		}
	}
	cur_len += i;
	i = 0;
	if (s3)
	{
		while (s3[i])
		{
			dst[cur_len + i] = s3[i];
			i++;
		}
	}
	dst[cur_len + i] = '\0';
	return (dst);
}

char	*ft_trijoin2(char *s1, char *s2, char *s3)
{
	char	*dst;
	size_t	i;
	size_t	cur_len;
	size_t	len_dst;

	len_dst = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	dst = malloc(sizeof(*dst) * len_dst + 1);
	if (!dst)
		return (0);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			dst[i] = s1[i];
			i++;
		}
	}
	cur_len = i;
	if (!s1)
		cur_len = 0;
	i = 0;
	if (s2)
	{
		while (s2[i])
		{
			dst[cur_len + i] = s2[i];
			i++;
		}
	}
	cur_len += i;
	i = 0;
	if (s3)
	{
		while (s3[i])
		{
			dst[cur_len + i] = s3[i];
			i++;
		}
	}
	dst[cur_len + i] = '\0';
	return (dst);
}

char	*ft_trijoin3(char *s1, char *s2, char *s3)
{
	char	*dst;
	size_t	i;
	size_t	cur_len;
	size_t	len_dst;

	len_dst = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	dst = malloc(sizeof(*dst) * len_dst + 1);
	if (!dst)
		return (0);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			dst[i] = s1[i];
			i++;
		}
	}
	cur_len = i;
	if (!s1)
		cur_len = 0;
	i = 0;
	if (s2)
	{
		while (s2[i])
		{
			dst[cur_len + i] = s2[i];
			i++;
		}
	}
	cur_len += i;
	i = 0;
	if (s3)
	{
		while (s3[i])
		{
			dst[cur_len + i] = s3[i];
			i++;
		}
	}
	dst[cur_len + i] = '\0';
	return (dst);
}
