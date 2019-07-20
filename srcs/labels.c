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

t_label		*first_label(t_lexem *test)
{
	t_label		*res;

	res = (t_label*)malloc(sizeof(t_label));
	res->value = ft_strdup(test->value);
	res->byte = test->position;
	res->next = NULL;
	res->prev = NULL;
	return (res);
}

t_label		*add_label(t_lexem *test, t_label *labels)
{
	t_label		*add;

	add = (t_label*)malloc(sizeof(t_label));
	add->value = ft_strdup(test->value);
	add->byte = test->position;
	add->next = NULL;
	add->prev = labels;
	labels->next = add;
	labels = add;

	return (labels);
}

t_label		*target_lables(t_lexem *test)
{
	t_label	*res;

	res = NULL;
	while (test)
	{
		if (test->type == 5)
		{
			if (!res)
				res = first_label(test);
			else
				res = add_label(test, res);
		}
		test = test->next;
	}
	while (res->prev)
		res = res->prev;
	return (res);
}