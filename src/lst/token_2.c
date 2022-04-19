/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:59:29 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/07 20:00:05 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_token_free_and_next(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	*token = (*token)->next;
	free(tmp->cmd);
	free(tmp);
}	

void	ft_token_free_and_sup(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	*token = (*token)->sup_token;
	free(tmp->cmd);
	free(tmp);
}	

void	ft_tokenclean_all(t_token **token)
{
	t_token	*tmp;

	while (*token)
	{
		if ((*token)->sub_token)
			*token = (*token)->sub_token;
		else if ((*token)->next)
			ft_token_free_and_next(token);
		else if ((*token)->sup_token)
			ft_token_free_and_sup(token);
		else
			ft_token_free_and_next(token);
	}
}
