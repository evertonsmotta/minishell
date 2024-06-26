# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nneto-de <nneto-de@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/23 17:19:17 by nneto-de          #+#    #+#              #
#    Updated: 2024/01/23 20:29:47 by nneto-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
LFLAGS = -lreadline

RM = rm -f
MAKE = make --no-print-directory -C

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = srcs/main.c \
		srcs/parsing/parser.c \
		srcs/parsing/tokenizer.c \
		srcs/parsing/tokenizer_utils.c \
		srcs/parsing/syntax_checker.c \
		srcs/parsing/expander.c \
		srcs/parsing/command_table.c \
		srcs/parsing/command_table_utils.c \
		srcs/environment/environment_lst.c \
		srcs/execution/executer.c \
		srcs/execution/redir_handler.c \
		srcs/execution/heredoc_handler.c \
		srcs/execution/pipes_handler.c \
		srcs/builtins/cd.c \
		srcs/builtins/echo.c \
		srcs/builtins/env.c \
		srcs/builtins/exit.c \
		srcs/builtins/export.c \
		srcs/builtins/pwd.c \
		srcs/builtins/unset.c \
		srcs/utils/main_utils.c \
		srcs/utils/parsing_utils.c \
		srcs/utils/execution_utils.c \
		srcs/utils/free_utils.c \
		srcs/utils/builtins_utils.c \
		srcs/utils/builtins_utils_2.c \
		srcs/signals/signal.c \
		srcs/signals/handlers.c \

S_OBJS = $(SRCS:.c=.o)

# ----------------------------------- RULES ------------------------------------

all: $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I.
	@printf "	Compiled$ $<\n"

$(NAME): $(S_OBJS)
	@$(MAKE) $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(LFLAGS) -o $(NAME)
	@echo "minishell was Created"

clean:
	@$(MAKE) $(LIBFT_DIR) clean
	@$(RM) $(S_OBJS)
	@echo "Deleted .o files"
	
fclean: clean
	@$(MAKE) $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@echo "Deleted executable"

re: fclean all

valgrind: all
	@valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

.PHONY: all clean fclean re
