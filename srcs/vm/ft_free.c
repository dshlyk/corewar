/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:57:53 by lgigi             #+#    #+#             */
/*   Updated: 2019/07/12 14:57:24 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	free_player(t_player *player)
{
	if (player->code)
		free(player->code);
	free(player);
}

void	free_carr(t_carriage *carr)
{
	t_carriage *tmp;

	while (carr)
	{
		tmp = carr;
		carr = carr->next;
		free(tmp);
	}
}

void	free_vm(t_vm *vm)
{
	int i;

	i = -1;
	while (++i < MAX_PLAYERS)
		if (vm->players[i])
			free_player(vm->players[i]);
	if (vm->carr)
		free_carr(vm->carr);
	free(vm);
}
