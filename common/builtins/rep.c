/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rep.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:51:11 by lyaiche           #+#    #+#             */
/*   Updated: 2022/05/08 18:25:41 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd(void)
{
	char	buffer[1024];

	if (!getcwd(buffer, sizeof(buffer)))
		return (-1);
	printf("%s\n", buffer);
	return (0);
}

int	cd_2(void)
{
	char	*home;

	home = my_getenv("HOME", NULL);
	if (home == NULL)
	{
		puterror("cd", "HOME not set");
		return (1);
	}
	chdir(home);
	return (0);
}

int	goto_dir(void)
{
	char	pwd_buff[1024];
	char	*pwd_var;
	char	*tmp;

	if (!getcwd(pwd_buff, sizeof(pwd_buff)))
		return (-1);
	pwd_var = my_getenv("PWD", NULL);
	if (pwd_var)
	{
		tmp = my_getenv("PWD", NULL);
		tmp = ft_strjoin("OLDPWD=", tmp);
		my_setenv(tmp);
		free(tmp);
		tmp = ft_strjoin("PWD=", pwd_buff);
		my_setenv(tmp);
		free(tmp);
	}
	return (0);
}

int	cd(char *cmd)
{
	char	**s_cmd;
	int		ret;

	ret = 0;
	s_cmd = ft_split2(cmd, " ");
	if (!s_cmd[1])
		return (cd_2());
	if (chdir(ft_ecrase_q(s_cmd[1])) == -1)
	{
		perror("cd");
		return (1);
	}
	else
		ret = goto_dir();
	ft_free_tab(s_cmd);
	return (ret);
}
