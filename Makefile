#=======================================#
#[MINISHELL] Fonctions partie principale#
#=======================================#

SRCS = 	src/main.c\
		\
		common/builtins/rep.c\
		common/builtins/echo.c\
		common/builtins/env.c\
		common/builtins/export.c\
		common/builtins/unset.c\
		common/builtins/utils.c\
		\
        libft/libft.a\
		common/signal/*.c\
		common/builtins/exit.c\
		\
		common/lst/*.c\
		common/utils/*\
		common/exec/*.c


#====#
#Tags#
#====#

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -lreadline -g -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew//opt/readline/include -fsanitize=address
OBJDIR = ./objs/
SRCDIR = ./src/
COMMONDIR = ./common/
INCLUDES = ./includes/

#=========#
#Commandes#
#=========#	

${OBJDIR}%.o : ${SRCDIR}%.c
								@gcc ${CFLAGS} -c $< -o $@ -I ${INCLUDES}

${OBJDIR}%.o : ${COMMONDIR}%.c
								@gcc ${CFLAGS} -c $< -o $@ -I ${INCLUDES}

$(NAME) :						${OBJDIR}
								make bonus -C libft
								@gcc ${CFLAGS} ${SRCS} -o ${NAME}

${OBJDIR}:						
								@mkdir -p ${OBJDIR}

all : $(NAME)

clean :
								make clean -C libft
								rm -rf ${OBJDIR}

fclean :						clean
								make fclean -C libft
								rm -f ${NAME}

re : 							fclean all

.PHONY :						all clean fclean re