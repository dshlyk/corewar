/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <lgigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 13:09:25 by lgigi             #+#    #+#             */
/*   Updated: 2019/07/19 13:03:47 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	sub(t_vm *vm, t_carriage *carr)
{
	carr->reg[carr->arg_vals[2] - 1] = carr->reg[carr->arg_vals[0] - 1]\
									- carr->reg[carr->arg_vals[1] - 1];
	carr->carry = (carr->reg[carr->arg_vals[2] - 1]) ? 0 : 1;
	if (vm->fl & FL_DEBUG3)
		ft_printf("P %4d | sub r%d r%d r%d\n", carr->pl, carr->arg_vals[0],
										carr->arg_vals[1], carr->arg_vals[2]);
}

void	and(t_vm *vm, t_carriage *carr)
{
	int val1;
	int val2;

	val1 = get_arg(vm, carr, 0);
	val2 = get_arg(vm, carr, 1);
	if (!(carr->reg[carr->arg_vals[2] - 1] = val1 & val2))
		carr->carry = 1;
	else
		carr->carry = 0;
	if (vm->fl & FL_DEBUG3)
		ft_printf("P %4d | and %d %d r%d\n", carr->pl, val1,
											val2, carr->arg_vals[2]);
}

void	or(t_vm *vm, t_carriage *carr)
{
	int val1;
	int val2;

	val1 = get_arg(vm, carr, 0);
	val2 = get_arg(vm, carr, 1);
	if (!(carr->reg[carr->arg_vals[2] - 1] = (val1 | val2)))
		carr->carry = 1;
	else
		carr->carry = 0;
	if (vm->fl & FL_DEBUG3)
		ft_printf("P %4d | or %d %d r%d\n", carr->pl, val1,
											val2, carr->arg_vals[2]);
}

void	xor(t_vm *vm, t_carriage *carr)
{
	int val1;
	int val2;

	val1 = get_arg(vm, carr, 0);
	val2 = get_arg(vm, carr, 1);
	if (!(carr->reg[carr->arg_vals[2] - 1] = (val1 ^ val2)))
		carr->carry = 1;
	else
		carr->carry = 0;
	if (vm->fl & FL_DEBUG3)
		ft_printf("P %4d | xor %d %d r%d\n", carr->pl, val1,
									val2, carr->arg_vals[2]);
}
