/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:59:14 by lyaiche           #+#    #+#             */
/*   Updated: 2022/05/05 00:02:03 by lxu-wu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_parsing2(t_token *sup_token)
{
	char	**tab;
	t_token	*token;
	t_token	*tmp;
	char	*line;

	line = tokenize(ft_ecrase_p(sup_token->cmd));
	tab = ft_split(line, "\1");
	free(line);
	token = ft_tab_to_token2(tab, sup_token);
	tmp = token;
	while (tmp)
	{
		ft_hdadd_back(&g_data->hd, ft_hd_finder(tmp->cmd));
		tmp->redirect = ft_init_redirect();
		if (tmp->cmd[0] == '(')
			tmp->sub_token = ft_parsing2(tmp);
		tmp = tmp->next;
	}
	return (token);
}

t_token	*ft_parsing(char *line)
{
	char	**tab;
	t_token	*token;
	t_token	*tmp;

	line = tokenize(line);
	tab = ft_split(line, "\1");
	token = ft_tab_to_token(tab);
	tmp = token;
	while (tmp)
	{
		ft_hdadd_back(&g_data->hd, ft_hd_finder(tmp->cmd));
		tmp->redirect = ft_init_redirect();
		if (tmp->cmd[0] == '(')
			tmp->sub_token = ft_parsing2(tmp);
		tmp = tmp->next;
	}
	return (token);
}
