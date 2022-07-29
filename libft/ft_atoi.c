/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 21:22:23 by lxu-wu            #+#    #+#             */
/*   Updated: 2022/04/06 16:15:40 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_return(int neg)
{
	if (neg == -1)
		return (0);
	else
		return (-1);
}

static int	ft_convert(const char *str, int neg)
{
	long long int	nbr;
	long long int	nbr2;
	long long int	nbr_tot;

	nbr_tot = 0;
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr_tot * 10;
		if (nbr / 10 != nbr_tot)
			return (ft_return(neg));
		nbr2 = *str - 48;
		nbr_tot = nbr + nbr2;
		if (nbr_tot < nbr || nbr_tot < nbr)
			return (ft_return(neg));
		str++;
	}
	return (nbr_tot * neg);
}

int	ft_atoi(const char *str)
{
	int				neg;

	if (str == NULL)
		return (0);
	while (*str == 32 || (*str && *str >= 9 && *str <= 13))
		str++;
	neg = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg *= -1;
		str++;
	}
	return (ft_convert(str, neg));
}
