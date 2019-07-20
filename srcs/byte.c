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

t_lexem		*start_write_command(int fd, t_lexem *test, t_label *labels)
{
	int 		i;
	int 		index;
	t_lexem		*fix;

	fix = test;
	index = index_detect(test->value);
	write_bytes(fd, g_operations[index].opcode, 1);
	test = test->next;
	i = 0;
	if (g_operations[index].codage)
        set_opcode_args(index, test, fd);
	while (i < g_operations[index].count_args)
	{
		if (test->type == 6)
			i += setter_reg(fd, test);
		else if (test->type == 8 || test->type == 9)
			i += setter_dir(test, labels, fd, fix);
        else if (test->type == 10 || test->type == 11)
        	i += setter_indir(test, labels, fd, fix);
		test = test->next;
	}
	return (test);
}


void	bytes(t_lexem *test, char *file)
{
    
     int			fd;
	 int			size_exec;
	 t_label		*labels;

	size_exec = get_size_exec(test);
	labels = target_lables(test);
	fd = open("lolkek", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (!fd || fd == -1)
		error("ERROR TO OPEN FILE");
	writer_to_file(fd, test, size_exec, labels);
	close(fd);
	exit(13);
}








