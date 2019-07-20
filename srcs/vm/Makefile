# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgigi <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/09 11:36:10 by lgigi             #+#    #+#              #
#    Updated: 2019/07/13 16:46:58 by lgigi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = corewar
CFLAGS = -Wall -Werror -Wextra
LIBFT_DIR = ../../libft/
INC = ./includes/
SRCS = parser.c errors.c ft_free.c main.c util.c print.c process_ops.c ops_utils.c ops.c ops2.c ops3.c ops4.c game.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SRCS)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -c $(SRCS) -I ../../$(INC) -I $(LIBFT_DIR)$(INC)
	$(CC) $(CFLAGS) $(OBJS) -o  $(NAME) -L $(LIBFT_DIR) -lft

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re