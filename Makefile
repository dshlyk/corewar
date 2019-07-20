# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vferry <vferry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/05 14:39:57 by vferry            #+#    #+#              #
#    Updated: 2019/07/15 14:29:01 by vferry           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

SRCS =	srcs/main.c\
		srcs/errors.c\
		srcs/inits.c\
		srcs/ALEX.c\
		srcs/byte.c\
		srcs/op.c\
		srcs/addit_funcs.c\
		srcs/write_to_file.c\
		srcs/labels.c\
		srcs/sizing.c\
		srcs/setters.c\

OBJS = $(patsubst srcs/%.c,objs/%.o,$(SRCS))
INCF = includes/
INCLB = libft/includes/
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

objs/%.o: srcs/%.c
	gcc -c $< -o $@ -I $(INCF) -I $(INCLB)

$(NAME): $(OBJS)
	make -C libft/
	gcc -o $(NAME) $(FLAGS) $(OBJS) -I $(INCF) -I $(INCLB) -L libft/ -lft

clean:
	make clean -C libft/
	rm -rf $(OBJS)

fclean: clean
	make fclean -C libft/
	rm -rf $(NAME)

re: fclean all