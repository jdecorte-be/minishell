<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte <jdecorte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 20:51:16 by jdecorte          #+#    #+#             */
/*   Updated: 2021/12/28 20:51:27 by jdecorte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
=======
>>>>>>> 032fb06ca1b34baf2ead7a4078944cdeea5fcb34

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

void	ft_error(int e);

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
int		ft_strcmp(char *s1, char *s2);
int		ft_isspace(char c);

// parite 1

void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);

void	ft_bzero(void *s, size_t n);

int		ft_memcmp(const void *s1, const void *s2, size_t n);

size_t	ft_strlen(const	char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);

int		ft_toupper(int c);
int		ft_tolower(int c);

int		ft_atoi(const char *str);

char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_strdup(const char *s1);
void	*ft_calloc(size_t count, size_t size);

// partie 2

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char *set);

char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// partie bonus

t_list	*ft_lstnew(void *content);
t_list	*ft_lstft_lstlast(t_list *lst);
t_list	*ft_lstlast(t_list *lst);

int		ft_lstsize(t_list *lst);

void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstadd_back(t_list **alst, t_list *new);

void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
