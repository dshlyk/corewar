/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <lgigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 13:28:56 by lgigi             #+#    #+#             */
/*   Updated: 2019/07/19 13:04:57 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	zjmp(t_vm *vm, t_carriage *carr)
{
	if (carr->carry)
		carr->pos = carr->pos + (carr->arg_vals[0] % IDX_MOD);
	else
		carr->pos += carr->to_next;
	if (vm->fl & FL_DEBUG3)
	{
		ft_printf("P %4d | zjmp %d ", carr->pl, carr->arg_vals[0]);
		ft_printf((carr->carry) ? "OK\n" : "FAILED\n");
	}
}

void	ldi(t_vm *vm, t_carriage *carr)
{
	int val1;
	int val2;

	val1 = get_arg(vm, carr, 0);
	val2 = get_arg(vm, carr, 1);
	carr->reg[carr->arg_vals[2] - 1] = rev_bytes_order(vm->field,
						carr->pos + ((val1 + val2) % IDX_MOD), 4);
	if (vm->fl & FL_DEBUG3)
	{
		ft_printf("P %4d | ldi %d %d r%d\n", carr->pl, val1,
											val2, carr->arg_vals[2]);
		ft_printf("%8c -> load from %d + %d = %d (with pc and mod %d)\n", '|',
				val1, val2, val1 + val2, carr->pos + ((val1 + val2) % IDX_MOD));
	}
}

void	sti(t_vm *vm, t_carriage *carr)
{
	int val1;
	int val2;

	val1 = get_arg(vm, carr, 1);
	val2 = get_arg(vm, carr, 2);
	write_to_field(vm, carr->reg[carr->arg_vals[0] - 1],
							carr->pos + ((val1 + val2) % IDX_MOD), 4);
	if (vm->fl & FL_DEBUG3)
	{
		ft_printf("P %4d | sti r%d %d %d\n", carr->pl, carr->arg_vals[0],
															val1, val2);
		ft_printf("%8c -> store to %d + %d = %d (with pc and mod %d)\n", '|',
			val1, val2, val1 + val2, carr->pos + ((val1 + val2) % IDX_MOD));
	}
}

void	op_fork(t_vm *vm, t_carriage *carr)
{
	carr_copy(carr, vm, carr->arg_vals[0] % IDX_MOD);
	if (vm->fl & FL_DEBUG3)
		ft_printf("P %4d | fork %d (%d)\n", carr->pl, carr->arg_vals[0],
											carr->arg_vals[0] % IDX_MOD);
}
