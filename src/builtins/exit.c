/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:27:52 by decortejohn       #+#    #+#             */
/*   Updated: 2022/04/01 21:54:48 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

long long		ft_atoi_exit(const char *str)
{
	int i;
	long neg;
	long long num;
    long long res;

	i = 0;
	neg = 1;
	num = 0;
    if((str[i] && (str[i] == '-') )|| (str[i] == '+'))
        if(str[i++] == '-')
            neg *= -1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - 48);
        if (((i == 18 && neg == 1) && (str[i] > '7' && str[i] <= '9'))
			|| ((i == 19 && neg == -1) && (str[i] == '9')))
            data->lastret = 2;
		i++;
	}
	return num * neg;
}

int exit_error(char *cmd)
{
    int i = 0;

    if(cmd[i] == '-' || cmd[i] == '+')
        i++;
    while(cmd[i])
    {
        if(!ft_isdigit(cmd[i]))
        {
            puterror(cmd, "numeric argument required");
            return 1;
        }
        i++;
    }
    return 0;
}

int exit_cmd(char **s_cmd)
{
    long long err = 0;
    if(!s_cmd[1])
    {
	    ft_free_tab(s_cmd);
        exit(0);
    }
    char *c_err = ft_ecrase_q(s_cmd[1]);
    if(exit_error(c_err) == 1)
    {
	    ft_free_tab(s_cmd);
        exit(-1);
    }
    if(s_cmd[2])
        ft_putstr_fd("bash: exit: too many arguments\n", 2);
    else
    {
        err = ft_atoi_exit(c_err);
        if(!(err < LONG_LONG_MAX && err > LONG_LONG_MIN))
        {
	        ft_free_tab(s_cmd);
            exit(-1);
        }
        data->lastret = err % 256;
    }
	ft_free_tab(s_cmd);
    exit(data->lastret);
}
