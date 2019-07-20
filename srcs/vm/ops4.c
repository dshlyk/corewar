/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <lgigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 14:06:04 by lgigi             #+#    #+#             */
/*   Updated: 2019/07/19 13:05:42 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	lld(t_vm *vm, t_carriage *carr)
{
	if (carr->arg_types[0] == T_DIR)
		carr->reg[carr->arg_vals[1] - 1] = carr->arg_vals[0];
	else if (carr->arg_types[0] == T_IND)
		carr->reg[carr->arg_vals[1] - 1] = rev_bytes_order(vm->field,
										carr->pos + (carr->arg_vals[0]), 4);
	carr->carry = (carr->reg[carr->arg_vals[1] - 1]) ? 0 : 1;
	if (vm->fl & FL_DEBUG3)
		ft_printf("P %4d | lld %d r%d\n", carr->pl, carr->arg_vals[0],
													carr->arg_vals[1]);
}

void	lldi(t_vm *vm, t_carriage *carr)
{
	int val1;
	int val2;

	val1 = get_arg(vm, carr, 0);
	val2 = get_arg(vm, carr, 1);
	carr->reg[carr->arg_vals[2] - 1] = rev_bytes_order(vm->field,
										carr->pos + ((val1 + val2)), 4);
	if (vm->fl & FL_DEBUG3)
	{
		ft_printf("P %4d | lldi %d %d r%d\n", carr->pl, val1,
											val2, carr->arg_vals[2]);
		ft_printf("%8s -> load from %d + %d = %d (with pc and mod %d)\n", "|",
							val1, val2, val1 + val2, carr->pos + (val1 + val2));
	}
}

void	lfork(t_vm *vm, t_carriage *carr)
{
	carr_copy(carr, vm, carr->arg_vals[0]);
	if (vm->fl & FL_DEBUG3)
		ft_printf("P %4d | lfork %d (%d)\n", carr->pl, carr->arg_vals[0],
														carr->arg_vals[0]);
}

void	aff(t_vm *vm, t_carriage *carr)
{
	ft_printf("%c", (char)carr->arg_vals[0]);
	if (vm->fl & FL_DEBUG3)
		ft_printf("P %4d | aff %d\n", carr->pl, carr->arg_vals[0]);
}
