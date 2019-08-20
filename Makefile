# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vferry <vferry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/03 16:09:03 by sbruen            #+#    #+#              #
#    Updated: 2019/07/27 18:13:34 by vferry           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME_VM = corewar
NAME_AS = asm
CFLAGS = -Wall -Werror -Wextra
LIBFT_DIR = ./libft/
INC = ./includes/
INCF = includes/
DIR = dir
INCLB = libft/includes/
SRCS_VM = srcs/vm/parser.c\
		srcs/vm/errors.c\
		srcs/vm/ft_free.c\
		srcs/vm/main.c\
		srcs/vm/util.c\
		srcs/vm/print.c\
		srcs/vm/process_ops.c\
		srcs/vm/ops_utils.c\
		srcs/vm/ops.c\
		srcs/vm/ops2.c\
		srcs/vm/ops3.c\
		srcs/vm/ops4.c\
		srcs/vm/game.c
SRCS_AS =	srcs/asm/main.c\
		srcs/asm/errors.c\
		srcs/asm/inits.c\
		srcs/asm/lexem_oth.c\
		srcs/asm/check_pct.c\
		srcs/asm/take_lex.c\
		srcs/asm/lexems.c\
		srcs/asm/lexems_frs.c\
		srcs/asm/lexems_sec.c\
		srcs/asm/lexems_thr.c\
		srcs/asm/help_funcs.c\
		srcs/asm/aleh_clean.c\
		srcs/asm/byte.c\
		srcs/asm/op.c\
		srcs/asm/addit_funcs.c\
		srcs/asm/write_to_file.c\
		srcs/asm/labels.c\
		srcs/asm/sizing.c\
		srcs/asm/setters.c\
		srcs/asm/print.c\
		srcs/asm/start_checking.c\
		srcs/asm/check_arguments.c\
		srcs/asm/check_separator.c\
		srcs/asm/check_label.c\
		srcs/asm/check_instructions.c\
		srcs/asm/check_champion.c\
		srcs/asm/check_helpers.c
OBJS_VM = $(patsubst srcs/vm/%.c,objs/vm/%.o,$(SRCS_VM))
OBJS_AS = $(patsubst srcs/asm/%.c,objs/asm/%.o,$(SRCS_AS))

objs/%.o: srcs/%.c
	@gcc -c $< -o $@ -I $(INCF) -I $(INCLB)\
		&& echo "\033[1m\033[36m$< \033[1m\033[32m--> \033[1m\033[31m$@\033[0m"

all: $(NAME_VM) $(NAME_AS)

$(NAME_VM): $(OBJS_VM)
	@echo "\n"
	@echo "\033[1m\033[34mCOMPILING LIBFT ...\033[0m"|tr -d '\n'
	@make -C libft/
	@echo " \033[1m\033[32mDONE\n\033[0m"
	@echo "\033[1m\033[34mCOMPILING  VM  ...\033[0m"|tr -d '\n'
	@$(CC) -o $(NAME_VM) $(FLAGS) $(OBJS_VM) -I $(INCF) -I $(INCLB) -L libft/ -lft
	@echo " \033[1m\033[32mDONE\033[0m\n\n"

$(NAME_AS): $(OBJS_AS)
	@echo "\033[1m\033[34mCOMPILING  ASM  ...\033[0m"|tr -d '\n'
	@$(CC) -o $(NAME_AS) $(FLAGS) $(OBJS_AS) -I $(INCF) -I $(INCLB) -L libft/ -lft
	@echo " \033[1m\033[32mDONE\033[0m\n\n"
	@echo " \n\n\t\t\033[1m\033[34m██████╗ ██████╗ ██████╗ ███████╗██╗    ██╗ █████╗ ██████╗ "
	@echo "\t\t\033[1m\033[34m██╔════╝██╔═══██╗██╔══██╗██╔════╝██║    ██║██╔══██╗██╔══██╗"
	@echo "\t\t\033[1m\033[34m██║     ██║   ██║██████╔╝█████╗  ██║ █╗ ██║███████║██████╔╝"
	@echo "\t\t\033[1m\033[34m██║     ██║   ██║██╔══██╗██╔══╝  ██║███╗██║██╔══██║██╔══██╗"
	@echo " \t\t\033[1m\033[34m╚██████╗╚██████╔╝██║  ██║███████╗╚███╔███╔╝██║  ██║██║  ██║"
	@echo " \t\t\033[1m\033[34m╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝ ╚══╝╚══╝ ╚═╝  ╚═╝╚═╝  ╚═╝"
	@echo "\n| | _____ _ __   _____      __    | |__   ___ "
	@echo "| |/ / __| '_ \ / _ \ \ /\ / /____| '_ \ / _ \ "
	@echo "|   <\__ \ | | | (_) \ V  V /_____| |_) |  __/"
	@echo "|_|\_\___/_| |_|\___/ \_/\_/      |_.__/ \___|\n"
	@echo "__   __/ _| ___ _ __ _ __ _   _ "
	@echo "\ \ / / |_ / _ \ '__| '__| | | |"
	@echo " \ V /|  _|  __/ |  | |  | |_| |"
	@echo "  \_/ |_|  \___|_|  |_|   \__, |"
	@echo " _                        |___/ "
	@echo "| | __ _( ) __ _( )"
	@echo "| |/ _  | |/ _  | |"
	@echo "| | (_| | | (_| | |"
	@echo "|_|\__, |_|\__, |_|"
	@echo "   |___/   |___/   "
	@echo "     _                           "
	@echo " ___| |__  _ __ _   _  ___ _ __  "
	@echo "/ __| '_ \| '__| | | |/ _ \ '_ \ "
	@echo "\__ \ |_) | |  | |_| |  __/ | | |"
	@echo "\___/_.__/|_|   \___/ \___|_| |_|\033[m\n"


clean:
	@rm -f $(OBJS_VM)
	@rm -rf $(OBJS_AS)
	@make clean -C ./libft

fclean: clean
	@rm -f $(NAME_VM)
	@rm -rf $(NAME_AS)
	@make fclean -C ./libft
	@rm -rf asm corewar

re: fclean all

.PHONY: clean fclean all re
