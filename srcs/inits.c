/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 13:28:50 by vferry            #+#    #+#             */
/*   Updated: 2019/07/07 14:09:39 by vferry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	init_cursor(t_cursor **s_cursor)
{
	( * s_cursor)->line = 0;
	( * s_cursor)->old_pos = 0;
	( * s_cursor)->pos = 0;
	( * s_cursor)->start = 0;
}

t_lexem *ft_cr_init_list(t_lexem *prev)
{
	t_lexem *next;

	next = (t_lexem *)malloc(sizeof(t_lexem));
	next->prev = prev;
	next->next = NULL;
	next->line = 0;
	next->start = 0;
	next->position = 0;
	next->type = -1;
	next->value = NULL;
	return (next);
}