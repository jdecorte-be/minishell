/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2021/12/28 20:50:53 by jdecorte          #+#    #+#             */
/*   Updated: 2021/12/28 20:50:56 by jdecorte         ###   ########.fr       */
=======
/*   Created: 2021/10/18 09:59:01 by lxu-wu            #+#    #+#             */
/*   Updated: 2021/12/21 09:45:35 by jdecorte         ###   ########.fr       */
>>>>>>> 032fb06ca1b34baf2ead7a4078944cdeea5fcb34
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *str, char *set)
{
	int	count;
	int	i;
	int	trigger;

	i = -1;
	count = 0;
	trigger = 0;
	while (str[++i] != '\0')
	{
		if (!ft_strchr(set, str[i]) && trigger == 0)
		{
			trigger = 1;
			count++;
		}
		else if (ft_strchr(set, str[i]))
			trigger = 0;
	}
	return (count);
}

static char	*ft_word_dup(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(sizeof(*word) * end - start + 1);
	if (!word)
		ft_error(2);
	while (start < end)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static char	**ft_to_create_tab(char **tab, const char *s, char *set)
{
	int		count;
	int		i;
	int		start;

	i = 0;
	count = 0;
	start = -1;
	while (i <= (int)ft_strlen(s))
	{
		if (!ft_strchr(set, s[i]) && start < 0)
			start = i;
		else if ((ft_strchr(set, s[i]) || i == (int)ft_strlen(s)) && start >= 0)
		{
			tab[count] = ft_word_dup(s, start, i);
			if (!tab[count] || !++count)
				ft_error(2);
			start = -1;
		}
		i++;
	}
	tab[count] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char *set)
{
	char	**tab;

	if (!s || !*s)
		return (0);
	tab = malloc(sizeof(char *) * (ft_count_words(s, set) + 1));
	if (!tab)
		ft_error(2);
	return (ft_to_create_tab(tab, s, set));
}
