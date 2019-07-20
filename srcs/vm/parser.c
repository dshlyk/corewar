/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <lgigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 11:26:29 by lgigi             #+#    #+#             */
/*   Updated: 2019/07/19 14:07:30 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				set_player(t_vm **vm, char *fname, int num)
{
	unsigned int	header;
	t_player		*player;

	player = init_player(vm);
	if ((player->fd = open(fname, O_RDONLY)) < 0)
		print_error(1, 0, player, *vm);
	player->num = num;
	if ((read(player->fd, &header, sizeof(int))) < 0)
		print_error(2, 0, player, *vm);
	if (reverse_bytes(header) != COREWAR_EXEC_MAGIC)
		print_error(3, 0, player, *vm);
	read(player->fd, player->name, PROG_NAME_LENGTH + 4);
	read(player->fd, &(player->code_size), 4);
	if ((player->code_size = reverse_bytes(player->code_size)) > CHAMP_MAX_SIZE)
		print_error(4, player->code_size, player, *vm);
	read(player->fd, player->comment, COMMENT_LENGTH + 4);
	if (!(player->code = (char *)malloc(sizeof(char) * player->code_size)))
		print_error(0, 0, player, *vm);
	if ((read(player->fd, player->code, player->code_size)) < player->code_size)
		print_error(5, player->code_size, player, *vm);
	(*vm)->players[num - 1] = player;
	if ((read(player->fd, &header, 1)) > 0)
		print_error(5, 0, player, *vm);
	ft_strclr(fname);
	close(player->fd);
}

static int			parse_n(t_vm **vm, int i, char **ag)
{
	int		num;

	num = 0;
	if (ag[i + 1] && (num = ft_atoi(ag[i + 1])) > 0)
	{
		if (ag[i + 2] && num <= MAX_PLAYERS)
		{
			if (!(*vm)->players[num - 1])
				set_player(vm, ag[i + 2], num);
			else
				print_error(6, 0, NULL, *vm);
		}
		else
			print_error(7, 0, NULL, *vm);
	}
	else
		print_error(7, 0, NULL, *vm);
	return (num);
}

static void			parse_debug(t_vm **vm, char **ag, int i)
{
	if (ag[i + 1] && ft_atoi(ag[i + 1]) == 1)
		(*vm)->fl |= FL_DEBUG1;
	else if (ag[i + 1] && ft_atoi(ag[i + 1]) == 2)
		(*vm)->fl |= FL_DEBUG2;
	else if (ag[i + 1] && ft_atoi(ag[i + 1]) == 4)
		(*vm)->fl |= FL_DEBUG3;
	if (ag[i + 1] && ft_isdigit(*ag[i + 1]))
		ft_strclr(ag[i + 1]);
	ft_strclr(ag[i]);
}

void				parse_flags(t_vm **vm, int ac, char **ag)
{
	int		i;

	i = 0;
	while (++i < ac)
	{
		if (!ft_strcmp("-dump", ag[i]) || !ft_strcmp("-d", ag[i]))
		{
			(*vm)->fl |= FL_DUMP;
			(*vm)->d_cycles = ft_atoi(ag[i + 1]);
			if (ag[i + 1] && ft_isdigit(*ag[i + 1]))
				ft_strclr(ag[i + 1]);
			ft_strclr(ag[i]);
		}
		else if (!ft_strcmp("-v", ag[i]))
			parse_debug(vm, ag, i);
		else if (!ft_strcmp("-n", ag[i]))
		{
			(parse_n(vm, i, ag)) ? ft_strclr(ag[i + 1]) : 0;
			ft_strclr(ag[i]);
		}
	}
}

t_vm				*parse_args(t_vm *vm, int ac, char **ag)
{
	int i;
	int j;

	i = 1;
	parse_flags(&vm, ac, ag);
	while (i < ac)
	{
		j = 0;
		if (*ag[i])
		{
			while (vm->players[j])
				j++;
			if (j >= 4)
				print_error(7, 0, NULL, vm);
			set_player(&vm, ag[i], ++j);
		}
		i++;
	}
	return (vm);
}
