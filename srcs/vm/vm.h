/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <lgigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:54:33 by lgigi             #+#    #+#             */
/*   Updated: 2019/07/19 13:21:39 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VM_H
# define FT_VM_H

# include "libft.h"
# include "op.h"

# define FL_DUMP (1 << 0)
# define FL_DEBUG1 (1 << 1)
# define FL_DEBUG2 (1 << 2)
# define FL_DEBUG3 (1 << 3)

# define ABS(a)( (a < 0) ? -(a) : (a))

typedef struct			s_player
{
	int					fd;
	int					num;
	char				name[PROG_NAME_LENGTH + 4];
	char				comment[COMMENT_LENGTH + 4];
	unsigned int		code_size;
	char				*code;
}						t_player;

typedef struct			s_carriage
{
	int					pl;
	size_t				pos;
	short				carry;
	short				op;
	int					alive;
	short				is_dead;
	unsigned int		arg_types[3];
	int					arg_vals[3];
	int					cycles;
	size_t				to_next;
	int					reg[REG_NUMBER];
	struct s_carriage	*next;
}						t_carriage;

typedef struct			s_vm
{
	short				fl;
	t_player			*last_live;
	unsigned int		live_operations;
	int					cycles_to_die;
	int					all_cycles;
	int					num_checks;
	unsigned int		d_cycles;
	t_carriage			*carr;
	t_player			*players[MAX_PLAYERS];
	unsigned char		field[MEM_SIZE];
}						t_vm;

void					live(t_vm *vm, t_carriage *carr);
void					ld(t_vm *vm, t_carriage *carr);
void					st(t_vm *vm, t_carriage *carr);
void					add(t_vm *vm, t_carriage *carr);
void					sub(t_vm *vm, t_carriage *carr);
void					and(t_vm *vm, t_carriage *carr);
void					or(t_vm *vm, t_carriage *carr);
void					xor(t_vm *vm, t_carriage *carr);
void					zjmp(t_vm *vm, t_carriage *carr);
void					ldi(t_vm *vm, t_carriage *carr);
void					sti(t_vm *vm, t_carriage *carr);
void					op_fork(t_vm *vm, t_carriage *carr);
void					lld(t_vm *vm, t_carriage *carr);
void					lldi(t_vm *vm, t_carriage *carr);
void					lfork(t_vm *vm, t_carriage *carr);
void					aff(t_vm *vm, t_carriage *carr);

typedef struct			s_operation
{
	unsigned short		op_code;
	unsigned short		num_args;
	short				carry;
	short				codage;
	int					cycles;
	short				label_size;
	unsigned int		args[3];
	void				(*f)(t_vm *vm, t_carriage *carr);
}						t_operation;

void					print_error(int err, unsigned int code_size,
											t_player *pl, t_vm *vm);
void					free_player(t_player *player);
void					free_carr(t_carriage *carr);
void					free_vm(t_vm *vm);
void					ft_exit(t_vm *vm, t_player *pl, int exit_st);
t_vm					*init_vm(int ac, char **ag);
t_player				*init_player(t_vm **vm);
t_vm					*parse_args(t_vm *vm, int ac, char **ag);
void					parse_flags(t_vm **vm, int ac, char **ag);
void					set_player(t_vm **vm, char *fname, int num);
unsigned int			reverse_bytes(unsigned int num);
void					introduce_players(t_player *pl[MAX_PLAYERS + 1]);
void					print_hex(t_vm *vm);
void					init_field(t_vm *vm, int i, int count);
void					init_carriage(t_vm **vm);
void					carr_push_front(t_carriage **carr, t_player *pl);
int						rev_bytes_order(unsigned char *field,
										size_t start, size_t n);
int						parse_args_codes(t_vm *vm, t_carriage *carr,
											int i, unsigned char cd);
void					swap_bytes(void *p, size_t s);
void					write_to_field(t_vm *vm, int val,
										size_t start, size_t n);
int						get_arg(t_vm *vm, t_carriage *carr, int ind);
void					carr_copy(t_carriage *carr, t_vm *vm, int pos);
void					game_routine(t_vm *vm, int i, t_carriage *cr);
void					print_winner(t_vm *vm);
void					print_usage(void);

extern const t_operation g_ops[16];

#endif
