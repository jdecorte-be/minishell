#include "../../inc/minishell.h"

t_token	*ft_tokennew(char *newcmd)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->cmd = newcmd;
	token->next = 0;
	// token->redirect = ft_init_redirect();
	return (token);
}