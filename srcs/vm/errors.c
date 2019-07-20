/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <lgigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:33:25 by lgigi             #+#    #+#             */
/*   Updated: 2019/07/19 12:54:31 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_exit(t_vm *vm, t_player *pl, int exit_st)
{
	if (pl)
		free_player(pl);
	if (vm)
		free_vm(vm);
	exit(exit_st);
}

void	print_error(int err, unsigned int code_size, t_player *pl, t_vm *vm)
{
	write(1, "Error! ", 7);
	if (err == 0)
		write(1, "Can't allocate memory\n", 22);
	else if (err == 1)
		write(1, "Not such file.\n", 15);
	else if (err == 2)
		write(1, "Permission denied!\n", 19);
	else if (err == 3)
		write(1, "File has an invalid header\n", 27);
	else if (err == 4)
		ft_printf("Player weight too large (%u > %u)",
							code_size, CHAMP_MAX_SIZE);
	else if (err == 5)
		write(1, "Invalid player code size!\n", 26);
	else if (err == 6)
		write(1, "Player already exist\n", 21);
	else if (err == 7)
		write(1, "Wrong player index!\n", 20);
	return (ft_exit(vm, pl, 1));
}
