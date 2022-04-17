#include "../../inc/minishell.h"

t_token	*ft_tokennew(char *newcmd)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->cmd = newcmd;
	token->sup_token = 0;
	token->sub_token = 0;
	token->next = 0;
	return (token);
}

t_token	*ft_sub_tokennew(char *newcmd, t_token *sup)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->cmd = newcmd;
	token->sup_token = sup;
	token->sub_token = 0;
	token->next = 0;
	// token->redirect = redirect;
	return (token);
}

t_token	*ft_tokenlast(t_token *token)
{
	t_token *tmp;

	if (!token)
		return (token);
	tmp = token;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}



void	ft_tokenadd_back(t_token **atoken, t_token *new)
{
	t_token	*last_elem;

	if (atoken && new)
	{
		if (!*atoken)
			*atoken = new;
		else
		{
			last_elem = ft_tokenlast(*atoken);
			last_elem->next = new;
		}
	}
}