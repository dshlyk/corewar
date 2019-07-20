# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfahey <mfahey@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/28 12:37:56 by vferry            #+#    #+#              #
#    Updated: 2019/05/22 20:16:10 by mfahey           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = srcs/accuracy.c\
		srcs/conver.c\
		srcs/field_width.c\
		srcs/flags1.c\
		srcs/flags2.c\
		srcs/flags3.c\
		srcs/ft_abs.c\
		srcs/ft_atoi.c\
		srcs/ft_bool.c\
		srcs/ft_bzero.c\
		srcs/ft_fabs.c\
		srcs/ft_floor.c\
		srcs/ft_fpart.c\
		srcs/ft_free_mas.c\
		srcs/ft_fuldel.c\
		srcs/ft_ipart.c\
		srcs/ft_isalnum.c\
		srcs/ft_isalpha.c\
		srcs/ft_isascii.c\
		srcs/ft_isdigit.c\
		srcs/ft_isprint.c\
		srcs/ft_itoa.c\
		srcs/ft_itoabase.c\
		srcs/ft_itoabase_size_p.c\
		srcs/ft_itoabasell.c\
		srcs/ft_lenstrm.c\
		srcs/ft_lstadd.c\
		srcs/ft_lstadend.c\
		srcs/ft_lstdel.c\
		srcs/ft_lstdelone.c\
		srcs/ft_lstiter.c\
		srcs/ft_lstmap.c\
		srcs/ft_lstnew.c\
		srcs/ft_max.c\
		srcs/ft_memalloc.c\
		srcs/ft_memccpy.c\
		srcs/ft_memchr.c\
		srcs/ft_memcmp.c\
		srcs/ft_memcpy.c\
		srcs/ft_memdel.c\
		srcs/ft_memmove.c\
		srcs/ft_memset.c\
		srcs/ft_min.c\
		srcs/ft_printf.c\
		srcs/ft_putchar.c\
		srcs/ft_putchar_fd.c\
		srcs/ft_putendl.c\
		srcs/ft_putendl_fd.c\
		srcs/ft_putnbr.c\
		srcs/ft_putnbr_fd.c\
		srcs/ft_putstr.c\
		srcs/ft_putstr_fd.c\
		srcs/ft_rfpart.c\
		srcs/ft_round.c\
		srcs/ft_str2len.c\
		srcs/ft_strcat.c\
		srcs/ft_strchr.c\
		srcs/ft_strclr.c\
		srcs/ft_strcmp.c\
		srcs/ft_strcpy.c\
		srcs/ft_strclen.c\
		srcs/ft_strdel.c\
		srcs/ft_strdup.c\
		srcs/ft_strequ.c\
		srcs/ft_striter.c\
		srcs/ft_striteri.c\
		srcs/ft_strjoin.c\
		srcs/ft_strlcat.c\
		srcs/ft_strlen.c\
		srcs/ft_strmap.c\
		srcs/ft_strmapi.c\
		srcs/ft_strncat.c\
		srcs/ft_strncmp.c\
		srcs/ft_strncpy.c\
		srcs/ft_strnequ.c\
		srcs/ft_strnew.c\
		srcs/ft_strnstr.c\
		srcs/ft_strrchr.c\
		srcs/ft_strsplit.c\
		srcs/ft_strstr.c\
		srcs/ft_strsub.c\
		srcs/ft_strtrim.c\
		srcs/ft_swap.c\
		srcs/ft_tolower.c\
		srcs/ft_toupper.c\
		srcs/get_next_line.c\
		srcs/htlpers1.c\
		srcs/htlpers2.c\
		srcs/htlpers3.c\
		srcs/ml_c_l.c\
		srcs/ml_h.c\
		srcs/ml_hh.c\
		srcs/ml_l.c\
		srcs/ml_ll.c\
		srcs/sv_zveno.c\
		srcs/type_csp.c\
		srcs/type_dioux.c\
		srcs/type_f.c\
		srcs/type_fs.c\
		srcs/type_proc.c\
		srcs/type_updupoupu.c

OBJS = $(patsubst srcs/%.c,objs/%.o,$(SRCS))
INC = includes/

all: $(NAME)

objs/%.o: srcs/%.c
	gcc -c $< -o $@ -I $(INC)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all