/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <lgigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 12:08:43 by lgigi             #+#    #+#             */
/*   Updated: 2019/07/19 13:03:18 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	live(t_vm *vm, t_carriage *carr)
{
	int i;

	i = 0;
	vm->live_operations++;
	carr->alive = vm->all_cycles;
	while (i < MAX_PLAYERS)
	{
		if (vm->players[i] && vm->players[i]->num == ABS(carr->arg_vals[0]))
		{
			vm->last_live = vm->players[i];
			if (vm->fl & FL_DEBUG1)
				ft_printf("Player %d (%s) is said to be alive\n",
						vm->players[i]->num, vm->players[i]->name);
			break ;
		}
		i++;
	}
	if (vm->fl & FL_DEBUG3)
		ft_printf("P %4d | live %d\n", carr->pl, carr->arg_vals[0]);
}

void	ld(t_vm *vm, t_carriage *carr)
{
	if (carr->arg_types[0] == T_DIR)
		carr->reg[carr->arg_vals[1] - 1] = carr->arg_vals[0];
	else if (carr->arg_types[0] == T_IND)
		carr->reg[carr->arg_vals[1] - 1] = rev_bytes_order(vm->field,
						carr->pos + (carr->arg_vals[0] % IDX_MOD), 4);
	carr->carry = (carr->reg[carr->arg_vals[1] - 1]) ? 0 : 1;
	if (vm->fl & FL_DEBUG3)
		ft_printf("P %4d | ld %d r%d\n", carr->pl, carr->arg_vals[0],
													carr->arg_vals[1]);
}

void	st(t_vm *vm, t_carriage *carr)
{
	if (carr->arg_types[1] == T_REG)
		carr->reg[carr->arg_vals[1] - 1] = carr->reg[carr->arg_vals[0] - 1];
	else if (carr->arg_types[1] == T_IND)
		write_to_field(vm, carr->reg[carr->arg_vals[0] - 1],
							carr->pos + (carr->arg_vals[1] % IDX_MOD), 4);
	if (vm->fl & FL_DEBUG3)
		ft_printf("P %4d | st r%d %d\n", carr->pl, carr->arg_vals[0],
													carr->arg_vals[1]);
}

void	add(t_vm *vm, t_carriage *carr)
{
	carr->reg[carr->arg_vals[2] - 1] = carr->reg[carr->arg_vals[0] - 1]\
										+ carr->reg[carr->arg_vals[1] - 1];
	if (carr->reg[carr->arg_vals[2] - 1])
		carr->carry = 0;
	else
		carr->carry = 1;
	if (vm->fl & FL_DEBUG3)
		ft_printf("P %4d | add r%d r%d r%d\n", carr->pl, carr->arg_vals[0],
										carr->arg_vals[1], carr->arg_vals[2]);
}
