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

int 	get_size_exec(t_lexem *test)
{
	int 	size;
	char 	*inst;

	size = 0;
	while (test)
	{
		test->position += size;
		if (test->type == 3)
		{
			size++;
			inst = ft_strdup(test->value);
			size += g_operations[index_detect(test->value)].codage;
		}
		if (test->type == 6 || test->type == 8 ||
				test->type == 9 || test->type == 10 || test->type == 11)
			size += arg_size(test, inst);
		test = test->next;
	}
	return (size);
}

int 	arg_size(t_lexem *test, char *inst)
{
	int 	index;
	int 	res;

	res = 0;
	index = index_detect(inst);
	if (index == -1)
		error("COMMAND DID NO FOUND");
	if (test->type == 9 || test->type == 8)
		res += g_operations[index].label_size;
	if (test->type == 6)
		res++;
	if (test->type == 10 || test->type == 11)
		res += 2;

	return (res);
}

void        set_opcode_args(int index, t_lexem *test, int fd)
{
    int     i;
    char    *types;

    types = ft_strnew(8);
    i = 0;
    while (i < g_operations[index].count_args)
    {
        if (test->type == 7)
            test = test->next;
        else
        {
            i++;
            if (test->type == 6)
                types = ft_strcat(types, "01");
            else if (test->type == 8 || test->type == 9)
                types = ft_strcat(types, "10");
            else if (test->type == 10 || test->type == 11)
                types = ft_strcat(types, "11");
            test = test->next;
        }
    }
    if (i == 3)
        types = ft_strcat(types, "00");
    if (i == 2)
        types = ft_strcat(types, "0000");
    if (i == 1)
        types = ft_strcat(types, "000000");
    write_bytes(fd, ft_atoi_base(types, 2), 1);
    free(types);
}