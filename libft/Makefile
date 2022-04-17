# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lxu-wu <lxu-wu@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/18 09:58:01 by lxu-wu            #+#    #+#              #
#    Updated: 2021/12/22 15:06:52 by lxu-wu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_isdigit.c ft_memset.c ft_strjoin.c ft_strtrim.c\
		ft_isprint.c ft_putchar_fd.c ft_strlcat.c ft_substr.c\
		ft_atoi.c ft_itoa.c ft_putendl_fd.c ft_strlcpy.c ft_tolower.c\
		ft_bzero.c ft_putnbr_fd.c ft_strlen.c ft_toupper.c ft_calloc.c\
		ft_memchr.c ft_putstr_fd.c ft_strmapi.c ft_isalnum.c ft_memcmp.c\
		ft_split.c ft_strncmp.c ft_isalpha.c ft_memcpy.c ft_strchr.c\
		ft_strnstr.c ft_isascii.c ft_memmove.c ft_strdup.c ft_strrchr.c\
		ft_striteri.c get_next_line.c ft_strcmp.c ft_isspace.c

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstlast.c ft_lstsize.c\
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c\
		ft_lstmap.c ft_lstmap.c ft_next.c

OBJS = ${SRCS:.c=.o}

OBJSBONUS = ${BONUS:.c=.o}

CC		= gcc
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror

all:	${NAME}

$(NAME): ${OBJS}
		ar rcs ${NAME} ${OBJS}

bonus:	${OBJS} ${OBJSBONUS}
		ar rcs ${NAME} ${OBJS} ${OBJSBONUS}

clean:
		${RM} ${OBJS} ${OBJSBONUS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re bonus
