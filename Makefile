NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -lreadline -g

RM = rm -rf

SRCS = 	src/main.c\
        src/utils.c\
		src/lexer.c\
		src/ft_error.c\
		src/executor.c\
		src/cleanstr.c\
		\
		src/builtins/cd.c\
		src/builtins/echo.c\
		src/builtins/env.c\
		src/builtins/export.c\
		\
        libft/libft.a\
		src/operator/pipex.c\
		src/utils/*\

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