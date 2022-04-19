/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trijoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 07:53:59 by lxu-wu            #+#    #+#             */
/*   Updated: 2022/04/20 23:30:47 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_trijoin_free(char *s1, char *s2, char *s3, int e)
{
	if (e == 1)
		free(s1);
	else if (e == 2)
		free(s2);
	else if (e == 3)
		free(s3);
	else if (e == 12 || e == 21)
	{
		free(s1);
		free(s2);
	}
	else if (e == 13 || e == 31)
	{
		free(s1);
		free(s3);
	}
	else if (e == 23 || e == 32)
	{
		free(s2);
		free(s3);
	}
}

char	*ft_trijoin(char *s1, char *s2, char *s3, int e)
{
	char	*str;
	char	*ret;

	str = malloc(sizeof(char) * (ft_strlen(s1)
				+ ft_strlen(s2) + ft_strlen(s3) + 1));
	ret = str;
	while (s1 && *s1)
		*str++ = *s1++;
	while (s2 && *s2)
		*str++ = *s2++;
	while (s3 && *s3)
		*str++ = *s3++;
	if (e)
		ft_trijoin_free(s1, s2, s3, e);
	*str = 0;
	return (ret);
}
