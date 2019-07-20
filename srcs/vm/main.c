/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <lgigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:18:47 by lgigi             #+#    #+#             */
/*   Updated: 2019/07/19 13:01:50 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_player			*init_player(t_vm **vm)
{
	t_player *player;

	if (!(player = (t_player *)malloc(sizeof(t_player))))
		print_error(0, 0, 0, *vm);
	player->code = NULL;
	return (player);
}

t_vm				*init_vm(int ac, char **ag)
{
	t_vm *vm;

	if (!(vm = (t_vm *)malloc(sizeof(t_vm))))
		return (NULL);
	vm->carr = NULL;
	vm->live_operations = 0;
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->num_checks = 0;
	vm->d_cycles = 0;
	vm->fl = 0;
	vm->all_cycles = 0;
	ft_bzero((void *)vm->players, sizeof(vm->players));
	ft_bzero((void *)vm->field, MEM_SIZE);
	return (parse_args(vm, ac, ag));
}

static void			set_carr_start(t_carriage *carr, int count, int part)
{
	while ((count -= part) && carr)
	{
		carr->pos = count;
		carr = carr->next;
	}
}

void				init_field(t_vm *vm, int i, int count)
{
	int	part;

	while (++i < MAX_PLAYERS)
		if (vm->players[i])
			count++;
	if (!count)
		ft_exit(vm, NULL, 1);
	part = MEM_SIZE / count;
	i = -1;
	count = 0;
	while (++i < MAX_PLAYERS)
	{
		if (vm->players[i])
		{
			ft_memcpy(&(vm->field[count]), vm->players[i]->code,
									vm->players[i]->code_size);
			count += part;
		}
	}
	init_carriage(&vm);
	set_carr_start(vm->carr, count, part);
}

int					main(int ac, char **ag)
{
	t_vm *vm;

	if (ac == 1 || !ft_strcmp("--help", ag[1]))
		print_usage();
	vm = init_vm(ac, ag);
	introduce_players(vm->players);
	init_field(vm, -1, 0);
	game_routine(vm, 0, NULL);
	ft_exit(vm, NULL, 1);
	return (0);
}
