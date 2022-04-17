NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -lreadline

RM = rm -rf

SRCS = 	src/main.c\
        src/utils.c\
		src/lexer.c\
		src/ft_error.c\
		\
		src/builtins/cd.c\
		src/builtins/echo.c\
		src/builtins/env.c\
		src/builtins/export.c\
		src/builtins/unset.c\
		\
        libft/libft.a\
		# src/pipex.c\

$(NAME) :
	make bonus -C libft
	gcc $(CFLAGS) $(SRCS) -o $(NAME)

all : $(NAME)

fclean : clean
	make fclean -C libft
	$(RM) $(NAME)

clean :
	make clean -C libft
	$(RM) $(NAME)

re : fclean all