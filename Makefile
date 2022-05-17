# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdecorte-be <jdecorte@proton.me>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 18:20:11 by jdecorte-be            #+#    #+#              #
#    Updated: 2022/05/17 17:38:17 by jdecorte-be         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================ Colors ==================================== #

RED			= \033[0;31m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
BLUE		= \033[0;34m
MAGENTA		= \033[0;35m
CYAN		= \033[0;36m
WHITE		= \033[0;37m
RESET		= \033[0m
BOLD		= \033[1m
DIM			= \033[2m

ECHO		= echo -e

# ================================ Project =================================== #

NAME		= minishell
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
LDFLAGS		= -lreadline
INCLUDES	= -I./includes

# =============================== Directories ================================ #

SRCDIR		= src
OBJDIR		= objs
LIBFTDIR	= libft

# ================================= Sources ================================== #

SRCS		= $(SRCDIR)/main.c \
			  $(SRCDIR)/builtins/rep.c \
			  $(SRCDIR)/builtins/echo.c \
			  $(SRCDIR)/builtins/env.c \
			  $(SRCDIR)/builtins/export.c \
			  $(SRCDIR)/builtins/unset.c \
			  $(SRCDIR)/builtins/utils.c \
			  $(SRCDIR)/builtins/exit.c \
			  $(wildcard $(SRCDIR)/signal/*.c) \
			  $(wildcard $(SRCDIR)/lst/*.c) \
			  $(wildcard $(SRCDIR)/utils/*.c) \
			  $(wildcard $(SRCDIR)/exec/*.c)

OBJS		= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
LIBFT		= $(LIBFTDIR)/libft.a

# ================================== Rules =================================== #

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(ECHO) "$(CYAN)$(BOLD)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)
	@$(ECHO) "$(GREEN)$(BOLD)✓ $(NAME) created successfully!$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(ECHO) "$(DIM)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(ECHO) "$(CYAN)$(BOLD)📚 Building libft...$(RESET)"
	@make bonus -C $(LIBFTDIR) > /dev/null 2>&1
	@$(ECHO) "$(GREEN)✓ libft ready$(RESET)"

clean:
	@$(ECHO) "$(YELLOW)🧹 Cleaning object files...$(RESET)"
	@make clean -C $(LIBFTDIR) > /dev/null 2>&1
	@rm -rf $(OBJDIR)
	@$(ECHO) "$(GREEN)✓ Clean complete!$(RESET)"

fclean: clean
	@$(ECHO) "$(YELLOW)🗑️  Removing executables...$(RESET)"
	@make fclean -C $(LIBFTDIR) > /dev/null 2>&1
	@rm -f $(NAME)
	@$(ECHO) "$(GREEN)✓ Full clean complete!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
