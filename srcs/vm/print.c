/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:36:58 by lgigi             #+#    #+#             */
/*   Updated: 2019/07/17 19:38:21 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	introduce_players(t_player *pl[MAX_PLAYERS])
{
	int i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < MAX_PLAYERS)
	{
		if (pl[i])
			ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
												pl[i]->num, pl[i]->code_size,
												pl[i]->name, pl[i]->comment);
		i++;
	}
}

void	print_hex(t_vm *vm)
{
	int				i;
	int				cnt;

	i = 0;
	cnt = 0;
	while (i < MEM_SIZE)
	{
		if (cnt == 0)
			ft_printf("0x%.4x : ", i);
		ft_printf("%02hhx", vm->field[i]);
		cnt++;
		ft_putchar((cnt == 32 ? '\n' : ' '));
		cnt = (cnt == 32) ? 0 : cnt;
		i++;
	}
}

void	print_winner(t_vm *vm)
{
	ft_printf("Contestant %d, \"%s\", has won !\n", vm->last_live->num,
													vm->last_live->name);
}

void	print_usage(void)
{
	ft_printf("Usage:\n./corewar [-dump N -v N -n N] [players]\n");
	ft_printf("-dump    : Dump memory after N cycles\n");
	ft_printf("-n N     : Choose order of champion\n");
	ft_printf("-v       : Verbosity levels of debug\n");
	ft_printf("           -1 : Show lives\n");
	ft_printf("           -2 : Show cycles\n");
	ft_printf("           -4 : Show operatins\n");
	exit(0);
}
