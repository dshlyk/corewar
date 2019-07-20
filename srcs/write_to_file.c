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

void		write_bytes(int fd, int a, int count_bytes)
{
	int				j;
	unsigned char	mass[count_bytes];

	j = count_bytes;
	while (count_bytes--)
	{
		mass[count_bytes] = (unsigned char)a;
		a = a >> 8;
	}
	while (++count_bytes < j)
		write(fd, &mass[count_bytes], 1);
}

void	writer_to_file(int fd, t_lexem *test, int size_exec, t_label *labels)
{
	set_name(fd, test);
	if (size_exec <= CHAMP_MAX_SIZE)
		write_bytes(fd, size_exec, 4);
	else
	{
		error("SIZE OF EXEC CODE IS TOO BIG");
	}
	set_comment(fd, test);
	set_exec_code(fd, test, labels);
}

void	set_name(int fd, t_lexem *test)
{
	int i;
	char *name_ex;


	i = -1;
	write_bytes(fd, COREWAR_EXEC_MAGIC, 4);

	while (test->next)
	{
		if (test->type == 1 && ft_strcmp(test->value, "name") == 0)
			name_ex = ft_strdup(test->next->value);
		test = test->next;
	}

	while (name_ex[++i])
		write_bytes(fd, name_ex[i], 1);
	write_bytes(fd, 0, PROG_NAME_LENGTH - ft_strlen(name_ex) + 4);
	free(name_ex);
}

void	set_comment(int fd, t_lexem *test)
{
	int		i;
	char	*comment;

	i = -1;
	while (test->next)
	{
		if (test->type == 1 && ft_strcmp(test->value, "comment") == 0)
			comment = ft_strdup(test->next->value);
		test = test->next;
	}
	while (comment[++i])
		write_bytes(fd, comment[i], 1);
	write_bytes(fd, 0, COMMENT_LENGTH - ft_strlen(comment) + 4);
	free(comment);
}

void	set_exec_code(int fd, t_lexem *test, t_label *labels)
{
	while (test)
	{
		if (test->type == 3)
			test = start_write_command(fd, test, labels);
		else
			test = test->next;
	}
}