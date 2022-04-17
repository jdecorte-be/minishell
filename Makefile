NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -lreadline

RM = rm -rf

SRCS = 	src/main.c\
        src/utils.c\
        libft/libft.a\

$(NAME) :
	make all -C libft
	gcc $(CFLAGS) $(SRCS) -o $(NAME)

all : $(NAME)

fclean : clean
	make fclean -C libft
	$(RM) $(NAME)

clean :
	make clean -C libft
	$(RM) $(NAME)

re : fclean all