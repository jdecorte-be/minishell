#include "../../inc/minishell.h"

char	**ft_list_to_tab(t_list *lst)
{
	char	**tab;
	size_t	i;

	tab = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!tab)
		ft_error(2);
	i = 0;
	while (lst)
	{
		tab[i++] = lst->content;
		lst = lst->next;
	}
	tab[i] = 0;
	return (tab);
}

t_list	*ft_tab_to_list(char **tab, t_list *lst)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		lst->content = tab[i++];
		lst = lst->next;
	}
	free(tab);
	return (lst);
}

t_token	*ft_tab_to_token(char **tab)
{
	size_t	i;
	t_token	*token;

	if (!tab || !*tab)
		return (0);
	token = 0;
	i = 0;
	while (tab[i])
	{
		ft_tokenadd_back(&token, ft_tokennew(tab[i++]));
	}
	free(tab);
	return (token);
}

int	ft_next_word(char *line, size_t i)
{
	char	c;

	while (line[i] && !ft_isspace(line[i]))
	{
		if (ft_strchr("\"\'", line[i]))
		{
			c = line[i++];
			while (line[i] && line[i] != c)
				i++;
			if (line[i])
				i++;
		}
		else
			i++;
	}
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (i);
}

int	ft_next_cmd(char *line, size_t i)
{
	while (line[i] && !ft_strchr("|&", line[i]))
		i++;
	while (line[i] && (ft_strchr("|&", line[i]) || ft_isspace(line[i])))
		i++;
	return (i);
}
