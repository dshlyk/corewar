/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 12:33:36 by vferry            #+#    #+#             */
/*   Updated: 2019/07/27 16:52:08 by vferry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "stdio.h"
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "op.h"

typedef struct			s_helper
{
	char				**file;
	char				**labels;
	int					count_labels;
	int					count_errors;
	int					count_lexem;
}						t_helper;

typedef struct			s_cursor
{
	int					line;
	int					pos;
	int					start;
	int					old_pos;
}						t_cursor;

typedef struct			s_lexem
{
	int					type;
	int					line;
	int					start;
	char				*value;
	int					position;
	struct s_lexem		*next;
	struct s_lexem		*prev;
}						t_lexem;

typedef struct			s_label
{
	int					byte;
	char				*value;
	struct s_label		*next;
	struct s_label		*prev;
}						t_label;

enum	e_tokens
{
	COMMAND = 1,
	STRING = 2,
	INSTRUCT = 3,
	COMMENT = 4,
	LABEL = 5,
	REG = 6,
	SEP = 7,
	DIR = 8,
	DIR_LABEL = 9,
	INDIR = 10,
	INDIR_LABEL = 11,
	UNDEF = 12
};

typedef struct			s_command
{
	char				*name;
	int					codage;
	int					count_args;
	int					label_size;
	int					args[3];
	int					opcode;
	int					number_byte;
	int					useless;
	int					useless2;
	struct s_command	*next;
}						t_command;

t_command				g_operations[17];
t_helper				*g_helper;

/*
** Функции ошибок и их вывода
*/
void					error(char *e);

/*
** Инициализация структур
*/
void					init_cursor(t_cursor **s_cursor);
t_lexem					*ft_cr_init_list(t_lexem *prev);

/*
** Байты вся хуйня
*/
void					bytes(t_lexem *test, char *file);
void					write_bytes(int fd, int a, int count_bytes);
void					set_name(int fd, t_lexem *test);
void					set_comment(int fd, t_lexem *test);
int						index_detect(char *opname);
t_lexem					*create_test_lexem(void);
int						get_size_exec(t_lexem *test);
int						arg_size(t_lexem *test, char *inst);
void					writer_to_file(int fd, t_lexem *test, int size_exec,
							t_label *labels);
t_label					*target_lables(t_lexem *test);
t_label					*first_label(t_lexem *test);
t_label					*add_label(t_lexem *test, t_label *labels);
void					set_exec_code(int fd, t_lexem *test, t_label *labels);
t_lexem					*start_write_command(int fd, t_lexem *test,
							t_label *labels);
void					set_opcode_args(int index, t_lexem *test, int fd);
void					set_indir_indirlabel(t_lexem *test, t_label *labels,
							int fd, t_lexem *fix);
void					set_dir_dirlabel(t_lexem *test, t_label *labels, int fd,
							t_lexem *fix);
int						setter_dir(t_lexem *test, t_label *labels, int fd,
							t_lexem *fix);
int						setter_indir(t_lexem *test, t_label *labels, int fd,
							t_lexem *fix);
void					set_dir_dirlabel(t_lexem *test, t_label *labels, int fd,
							t_lexem *fix);
int						setter_reg(int fd, t_lexem *test);
int						ft_atoi_base(const char *str, int str_base);
void					addit_binary(int i, char *types, int fd);
char					*extract_name(char *str);

/*
** ALEX
*/
int						ft_is_symbol(char **file, t_cursor *cur);
int						ft_is_only_symbol(char **file, t_cursor **cur);
int						ft_only_dig(char *line, t_cursor **cur);
int						ft_is_undef(char c);
int						ft_lable_check_chars(t_cursor **cur, char **file);
int						ft_lable_chars(t_cursor **cur, char **file);
t_lexem					*ft_labch_lex(t_cursor **cur, char **file,
							t_lexem *list);
t_lexem					*ft_instruct_lex(t_cursor **cur, char **file,
							t_lexem *list);
t_lexem					*ft_direct_lex(t_cursor **cur, char **file,
							t_lexem *list);
t_lexem					*ft_direct_lab_lex(t_cursor **cur, char **file,
							t_lexem *list);
t_lexem					*ft_plus_lex(t_cursor **cur, char **file,
							t_lexem *list);
t_lexem					*ft_minus_lex(t_cursor **cur, char **file,
							t_lexem *list);
t_lexem					*ft_hand_diglex(t_cursor **cur, char **file,
							t_lexem *list);
t_lexem					*ft_reg_lex(t_cursor **cur, char **file, t_lexem *list);
t_lexem					*ft_regchar_lexm(t_cursor **cur, char **file,
							t_lexem *list);
t_lexem					*ft_instal_lexm(t_cursor **cur, char **file,
							t_lexem *list);
t_lexem					*ft_check_pct(t_cursor **cur, char **file,
							t_lexem *list);
t_lexem					*ft_handling_sep(t_cursor **cur, t_lexem *list);
t_lexem					*ft_handling_oktotopr(t_cursor **cur, t_lexem *list);
t_lexem					*ft_indir_lexem(t_cursor **cur, char **file,
							t_lexem *list);
t_lexem					*ft_p_m_lex(t_cursor **cur, char **file, t_lexem *list);
t_lexem					*ft_low_line_lex(t_cursor **cur, char **file,
							t_lexem *list);
t_lexem					*ft_undef_lex(t_cursor **cur, char **file,
							t_lexem *list);
void					print_struct(t_lexem *bitch, char fl);
void					ft_clean_file(char **file);
void					ft_clean_lex(t_lexem *del);

/*
** from main
*/
int						check_format(char *name);
int						ft_is_undef(char c);
t_lexem					*ft_undef_lex(t_cursor **cur, char **file,
							t_lexem *list);
t_lexem					*ft_hand_point(t_cursor **cur, char **file,
							t_lexem *list);
t_lexem					*ft_hand_string(t_cursor **cur, char **file,
							t_lexem *list);
void					ft_take_lex(char **file, t_cursor *cur, t_lexem **list);
void					ft_mount_token(t_lexem *new, t_cursor *cur,
							char **file);

/*
** Ашыбки
*/
t_lexem					*check_next_lexem(t_lexem *lexem);
void					ft_error(char *error, t_lexem *lexem);
void					init_structs(t_lexem *lexem, char **file, int lines);
void					start_checking(t_lexem *lexem, char **file, int i);
t_lexem					*check_separator(t_lexem *lexem);
int						check_label(char *label);
int						is_number(char *num);
void					check_reg_argument(t_lexem *lexem);
void					check_label_argument(t_lexem *lexem);
void					check_dir_indir_argument(t_lexem *lexem);
int						check_argument_type(t_lexem *lexem, int i, int j);
t_lexem					*check_instructions_arguments(t_lexem *lexem,
							int inst_index);
int						check_instruction_names(t_lexem *lexem);
t_lexem					*check_instructions(t_lexem *lexem);
t_lexem					*check_string(t_lexem *lexem);
t_lexem					*check_name(t_lexem *lexem);
t_lexem					*check_champion(t_lexem *lexem);
t_lexem					*check_comment(t_lexem *lexem);
void					print_arr(char **arr);
t_lexem					*error_next_lexem(t_lexem *lexem, char *error);
void					errors_check(void);
void					memory_cleaner(void);
t_lexem					*check_extra_separators(t_lexem *lexem);
void					count_lexems(t_lexem *lexem);
void					check_eof(void);

#endif
