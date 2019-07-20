/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <lgigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 12:57:41 by lgigi             #+#    #+#             */
/*   Updated: 2019/07/19 13:27:39 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	write_to_field(t_vm *vm, int val, size_t start, size_t n)
{
	void			*ptr;
	unsigned char	*v;

	swap_bytes((void *)&val, n);
	ptr = (void *)&val;
	v = (unsigned char *)ptr;
	while (n--)
		vm->field[start++ % MEM_SIZE] = *v++;
}

int		get_arg(t_vm *vm, t_carriage *carr, int ind)
{
	int res;

	res = 0;
	if (carr->arg_types[ind] == T_REG)
		res = carr->reg[carr->arg_vals[ind] - 1];
	else if (carr->arg_types[ind] == T_DIR)
		res = carr->arg_vals[ind];
	else if (carr->arg_types[ind] == T_IND)
		res = rev_bytes_order(vm->field,
					carr->pos + (carr->arg_vals[ind] % IDX_MOD), 4);
	return (res);
}

void	carr_copy(t_carriage *carr, t_vm *vm, int pos)
{
	int i;

	i = -1;
	carr_push_front(&(vm->carr), vm->players[carr->pl - 1]);
	while (++i < REG_NUMBER)
		vm->carr->reg[i] = carr->reg[i];
	vm->carr->alive = carr->alive;
	vm->carr->pos = (carr->pos + pos) % MEM_SIZE;
	vm->carr->carry = carr->carry;
}
