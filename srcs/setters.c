/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 15:49:14 by ksnow-be          #+#    #+#             */
/*   Updated: 2019/07/17 12:48:59 by vferry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int 		setter_reg(int fd, t_lexem *test)
{
	write_bytes(fd, ft_atoi(test->value), T_REG);
	return (1);
}

int 		setter_dir(t_lexem *test, t_label *labels, int fd, t_lexem *fix)
{
	set_dir_dirlabel(test, labels, fd, fix);
	return (1);
}

int 		setter_indir(t_lexem *test, t_label *labels, int fd, t_lexem *fix)
{
	set_indir_indirlabel(test, labels, fd, fix);
	return (1);
}

void		set_dir_dirlabel(t_lexem *test, t_label *labels, int fd, t_lexem *fix)
{
	int 	index;

	index = index_detect(fix->value);
	if (test->type == 9)
	{
		while (labels)
		{
			if (ft_strcmp(test->value, labels->value) == 0)
				write_bytes(fd, labels->byte - fix->position, g_operations[index].label_size);
			labels = labels->next;
		}
	}
	else if (test->type == 8)
		write_bytes(fd, ft_atoi(test->value), g_operations[index].label_size);
}

void    set_indir_indirlabel(t_lexem *test, t_label *labels, int fd, t_lexem *fix)
{
    if (test->type == 11)
    {
		while (labels)
		{
			if (ft_strcmp(test->value, labels->value) == 0)
				write_bytes(fd, labels->byte - fix->position, 2);
			labels = labels->next;
		}
    }
    else if (test->type == 10)
        write_bytes(fd, ft_atoi(test->value), 2);
}