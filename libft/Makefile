# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgigi <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/03 19:20:06 by lgigi             #+#    #+#              #
#    Updated: 2019/05/24 12:39:42 by lgigi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc
NAME		= libft.a
INCLUDES	= ./includes/
SOURCES		= ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c  ft_toupper.c ft_tolower.c ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_isspace.c ft_str_is_alpha.c ft_str_is_lowercase.c ft_str_is_numeric.c ft_str_is_printable.c ft_str_is_uppercase.c ft_strcut.c ft_strcapitalize.c ft_strupcase.c ft_strlowcase.c get_next_line.c
FT_PRINTF_FILES = ft_ltoa.c ft_print_scp.c ft_printf_diox.c ft_utoa.c ft_printf.c ft_parse.c ft_print_fl.c utils.c checks.c  buffer.c
FT_PRINTF_SRC = $(addprefix ./ft_printf/, $(FT_PRINTF_FILES))
FT_PRINTF_OBJ = $(FT_PRINTF_FILES:.c=.o)
CFLAGS		  = -Wall -Werror -Wextra  -c
OBJ			  = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(SOURCES) $(FT_PRINTF_SRC)
	@$(CC) $(CFLAGS) $(SOURCES) $(FT_PRINTF_SRC) -I $(INCLUDES)
	@ar rc $(NAME) $(OBJ) $(FT_PRINTF_OBJ)
	@ranlib $(NAME)

clean:
	@rm -f $(OBJ) $(FT_PRINTF_OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

so:
	@$(CC) -g -fPIC -Wall -Werror -Wextra $(SOURCES) $(FT_PRINTF_SRC) -shared -o $(NAME:.a=.so)

.PHONY: clean fclean all re so
