/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rep.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:51:11 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/15 13:33:54 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pwd(void)
{
	char	buffer[1024];

	if (!getcwd(buffer, sizeof(buffer)))
		return (-1);
	printf("%s\n", buffer);
	return (0);
}

int	cd_2(char **cmd)
{
	char	*home;

	home = my_getenv("HOME", NULL);
	if (home == NULL)
	{
		puterror("cd", "HOME not set");
		return (1);
	}
	chdir(home);
	ft_free_tab(cmd);
	return (0);
}

int	cd_3(char **cmd)
{
	perror("cd");
	ft_free_tab(cmd);
	return (1);
}

int	cd(char **cmd)
{
	char	pwd_buff[1024];
	char	*pwd_var;
	char	*tmp;

	if (!cmd[1])
		return (cd_2(cmd));
	if (chdir(ft_ecrase_q(cmd[1])) == -1)
		return (cd_3(cmd));
	else
	{
		if (!getcwd(pwd_buff, sizeof(pwd_buff)))
		{
			ft_free_tab(cmd);
			return (-1);
		}
		pwd_var = my_getenv("PWD", NULL);
		if (pwd_var)
		{
			tmp = my_getenv("PWD", NULL);
			my_setenv(ft_strjoin("OLDPWD=", tmp));
			my_setenv(ft_strjoin("PWD=", pwd_buff));
		}
	}
	ft_free_tab(cmd);
	return (0);
}
