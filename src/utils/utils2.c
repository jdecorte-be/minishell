#include "../../inc/minishell.h"

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_strncmp2(const char *s1, const char *s2, size_t n)
{
	size_t			i;

	i = 0;
	// printf("nn %s == %s\n", s1, s2);
	while (i < n && ((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
		i++;
	// printf("nn %d\n", ((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

int	ft_strrcmp2(const char *s1, const char *s2, size_t n)
{
	size_t			i;

	i = n;
	// printf("rr %s == %s\n", s1, s2);
	while (*(unsigned char *)s1)
		s1++;
	while (i && (*(unsigned char *)s1 == ((unsigned char *)s2)[i]))
	{
		s1--;
		i--;
	}
	// printf("rr %c, %c\n", ((unsigned char *)s1)[i], ((unsigned char *)s2)[i]);
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

void	ft_lstdel(t_list **lst, t_list *elem)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *lst;
	while (tmp && (tmp)->next && (tmp)->next != elem && (tmp) != elem)
		tmp = (tmp)->next;
	if ((tmp)->next)
	{
		tmp2 = tmp->next;
		tmp->next = tmp2->next;
		free(tmp2->content);
		free(tmp2);
	}
}

// char	*ft_cutoff(char *str, size_t start, size_t len)
// {
// 	char	*newstr;
// 	size_t	i;
// 	size_t	i2;

// 	i = 0;
// 	i2 = 0;
// 	newstr = malloc(sizeof(char) * (ft_strlen(str) - len + 1));
// 	while (str[i])
// 	{
// 		if (i < start || i >= start + len)
// 			newstr[i2++] = str[i++];
// 		else
// 			i++;
// 	}
// 	newstr[i2] = 0;
// 	return (newstr);
// }

// hello bye salute salutation = 27
// hellosalute salutation = 22 
