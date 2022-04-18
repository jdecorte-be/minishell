/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: decortejohn <decortejohn@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:27:52 by decortejohn       #+#    #+#             */
/*   Updated: 2022/01/31 00:15:41 by decortejohn      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int exit_cmd(char **s_cmd)
{
        int i  = 0;
        while(s_cmd[1][i])
        {
            if(!ft_isdigit(s_cmd[1][i]))
                return 255;
            i++;
        }
        // printf("exit\n");
        if(s_cmd[2])
        {
            ft_putstr_fd("bash: exit: too many arguments\n", 2);
            return 1;
        }
        else if (s_cmd[1][0] == '+' && ft_isdigit(s_cmd[1][1]))
            return 0;
        else if ((s_cmd[1][0] == '-' && ft_isdigit(s_cmd[1][1])))
            return 2;
        else if (((s_cmd[1][0] == '-' || s_cmd[1][0] == '+') && (s_cmd[1][1] == '-' || s_cmd[1][1] == '+'))|| (s_cmd[1][0] == '-'  && ft_isdigit(s_cmd[1][1])))
            return 2;
        exit(ft_atoi(s_cmd[1]));

        return 0;
}
