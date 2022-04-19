/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdollar_hd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaiche <lyaiche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:46:04 by lyaiche           #+#    #+#             */
/*   Updated: 2022/04/06 18:50:23 by lyaiche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_chdollar_ok_hd(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] && line[i] == '$')
			return (0);
		else if (line[i])
			i++;
	}
	return (1);
}

char	*ft_changedollar_hd(char *line, t_list **dollar)
{
	char	*str;

	if (ft_isdigit(line[0]))
		str = 0;
	else if (ft_strncmp(line, "$?", 1))
		str = ft_strdup(getenv(line + 1));
	else if (!ft_strncmp(line, "$?", 1))
		str = ft_itoa(g_data->lastret);
	else
		str = 0;
	ft_lstadd_back(dollar, ft_lstnew(str));
	free(line);
	return (str);
}

size_t	ft_chdollar_len_hd(char *line, t_list **dollar)
{
	size_t	i;
	long	count;
	long	start;
	long	end;

	i = 0;
	count = 0;
	while (line[i])
	{	
		if (line[i] && line[i + 1] && line[i] == '$' &&
			(ft_isalnum(line[i + 1]) || ft_strchr("?", line[i + 1])))
		{
			start = i++;
			if (ft_strchr("\'\"", line[i]) && ++i)
				count--;
			else if (line[i] == '?' || ft_isdigit(line[i]))
			{
				count += -2;
				count += ft_strlen(ft_changedollar_hd(ft_substr(line,
								start, end - start), dollar));
			}
			else
			{
				while (line[i] && (ft_isalnum(line[i])
						|| ft_strchr("?", line[i])))
					i++;
				end = i;
				count += start - end;
				count += ft_strlen(ft_changedollar_hd(ft_substr(line,
								start, end - start), dollar));
			}
		}
		else
			i++;
	}
	return (i + count);
}

char	*ft_chdollar_str_hd(char *str, char *line, t_list *dollar, size_t len)
{
	size_t	i;
	size_t	i2;
	t_list	*tmp;

	i = 0;
	i2 = 0;
	while (line[i])
	{
		if (line[i] && line[i + 1] && line[i] == '$' && (ft_isalnum(line[i + 1])
				|| ft_strchr("?", line[i + 1])) && ++i)
		{
			if ((line[i] == '?' || ft_isdigit(line[i])) && ++i)
			{
				i2 = ft_strlcat(str, dollar->content, len);
				dollar = ft_next(dollar);
			}
			else
			{
				while (line[i] && (ft_isalnum(line[i])
						|| ft_strchr("?", line[i])))
					i++;
				i2 = ft_strlcat(str, dollar->content, len);
				dollar = ft_next(dollar);
			}
		}
		else if (line[i] && line[i] == '$' && line[i + 1]
			&& ft_strchr("\'\"", line[i + 1]))
			i++;
		else if (line[i])
		{
			str[i2++] = line[i++];
		}
	}
	str[i2] = 0;
	return (str);
}

char	*ft_chdollar_hd(char *line)
{
	size_t	len;
	char	*str;
	t_list	*dollar;

	if (!line)
		return (0);
	if (ft_chdollar_ok_hd(line))
		return (line);
	dollar = 0;
	len = ft_chdollar_len_hd(line, &dollar);
	str = ft_calloc(sizeof(*str), len + 1);
	str = ft_chdollar_str_hd(str, line, dollar, len);
	free(line);
	return (str);
}
