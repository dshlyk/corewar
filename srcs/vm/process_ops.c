/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <lgigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 18:03:58 by lgigi             #+#    #+#             */
/*   Updated: 2019/07/19 13:17:12 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

const t_operation g_ops[16] =
{
	{1, 1, 0, 0, 10, 4, {T_DIR, 0, 0}, &live},
	{2, 2, 1, 1, 5, 4, {T_DIR | T_IND, T_REG, 0}, &ld},
	{3, 2, 0, 1, 5, 4, {T_REG, T_REG | T_IND, 0}, &st},
	{4, 3, 1, 1, 10, 4, {T_REG, T_REG, T_REG}, &add},
	{5, 3, 1, 1, 10, 4, {T_REG, T_REG, T_REG}, &sub},
	{6, 3, 1, 1, 6, 4,\
		{T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}, &and},
	{7, 3, 1, 1, 6, 4,\
		{T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}, &or},
	{8, 3, 1, 1, 6, 4,\
		{T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG}, &xor},
	{9, 1, 0, 0, 20, 2, {T_DIR, 0, 0}, &zjmp},
	{10, 3, 0, 1, 25, 2, {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG}, &ldi},
	{11, 3, 0, 1, 25, 2, {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR}, &sti},
	{12, 1, 0, 0, 800, 2, {T_DIR, 0, 0}, &op_fork},
	{13, 2, 1, 1, 10, 4, {T_DIR | T_IND, T_REG, 0}, &lld},
	{14, 3, 1, 1, 50, 2, {T_REG | T_DIR | T_IND, T_REG | T_IND, T_REG}, &lldi},
	{15, 1, 0, 0, 1000, 2, {T_DIR, 0, 0}, &lfork},
	{16, 1, 0, 1, 2, 4, {T_REG, 0, 0}, &aff}
};

static size_t	set_tonext(unsigned int *types, unsigned short op)
{
	size_t	next;
	int		i;

	i = 0;
	next = 0;
	while (i < g_ops[op - 1].num_args)
	{
		if (types[i] == T_DIR)
			next += g_ops[op - 1].label_size;
		else if (types[i] == T_REG)
			next += 1;
		else if (types[i] == T_IND)
			next += 2;
		i++;
	}
	return (next);
}

int				rev_bytes_order(unsigned char *field, size_t start, size_t n)
{
	int				res;
	int				sign;
	void			*ptr;
	unsigned char	*arr;

	res = 0;
	sign = (field[start % MEM_SIZE] & 0x80);
	ptr = (void *)&res;
	arr = (unsigned char *)ptr;
	while (n--)
		arr[n] = (sign) ? field[start++ % MEM_SIZE] ^ 0xFF\
								: field[start++ % MEM_SIZE];
	res = (sign) ? ~(res) : res;
	return (res);
}

static int		proccess_carr_args(t_carriage *carr, unsigned int *types,
														unsigned short op)
{
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	while (i < g_ops[op - 1].num_args)
	{
		if ((types[i] == DIR_CODE) && ++cnt)
			types[i] = T_DIR;
		else if ((types[i] == IND_CODE) && ++cnt)
			types[i] = T_IND;
		else if ((types[i] == REG_CODE) && ++cnt)
			types[i] = T_REG;
		i++;
	}
	if (cnt < g_ops[op - 1].num_args)
	{
		carr->to_next += set_tonext(types, op);
		return (0);
	}
	return (1);
}

static int		get_arg_vals(t_vm *vm, t_carriage *carr)
{
	int		i;
	int		start_pos;
	int		step;

	i = 0;
	step = 0;
	start_pos = carr->to_next;
	carr->to_next += set_tonext(carr->arg_types, carr->op);
	while (i < g_ops[carr->op - 1].num_args)
	{
		if (!(g_ops[carr->op - 1].args[i] & carr->arg_types[i]))
			return (0);
		if (carr->arg_types[i] == T_DIR)
			step = g_ops[carr->op - 1].label_size;
		else if (carr->arg_types[i] == T_REG)
			step = 1;
		else if (carr->arg_types[i] == T_IND)
			step = 2;
		carr->arg_vals[i] = rev_bytes_order(vm->field,
							carr->pos + start_pos, step);
		start_pos += step;
		i++;
	}
	return (1);
}

int				parse_args_codes(t_vm *vm, t_carriage *carr,
									int i, unsigned char cd)
{
	if (carr->op > 16 || !carr->op)
	{
		carr->to_next = 1;
		return (0);
	}
	else if (g_ops[carr->op - 1].codage\
		&& !vm->field[(carr->pos + 1) % MEM_SIZE])
	{
		carr->to_next = 2;
		return (0);
	}
	else if (!g_ops[carr->op - 1].codage && (carr->to_next = 1))
		while (++i < 3)
			carr->arg_types[i] = g_ops[carr->op - 1].args[i];
	if (i == -1 && g_ops[carr->op - 1].codage)
	{
		cd = (vm->field[(carr->pos + 1) % MEM_SIZE]);
		carr->arg_types[++i] |= ((cd >> 6) & 3);
		while ((cd <<= 2))
			carr->arg_types[++i] |= ((cd >> 6) & 3);
		carr->to_next = 2;
		if (!proccess_carr_args(carr, carr->arg_types, carr->op))
			return (0);
	}
	return (get_arg_vals(vm, carr));
}
