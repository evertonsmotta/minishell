# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nneto-de <nneto-de@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/23 17:19:17 by nneto-de          #+#    #+#              #
#    Updated: 2024/01/23 19:51:58 by nneto-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -------------------------------- VARIABLES -----------------------------------

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm -f
AR = ar -rcs

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
		ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
		ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \
		printf/ft_print_c.c printf/ft_printf.c printf/ft_print_n.c \
		printf/ft_print_p.c printf/ft_print_s.c printf/ft_print_u.c \
		printf/ft_print_x.c gnl/get_next_line.c gnl/get_next_line_utils.c \
		ft_swap.c ft_strcmp.c

S_OBJS = $(SRCS:.c=.o)

# ---------------------------------- RULES -------------------------------------

all: $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I.

$(NAME): $(S_OBJS)
	@$(AR) $(NAME) $(S_OBJS)

clean:
	@$(RM) $(S_OBJS) $(B_OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
