/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <lgigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:22:28 by lgigi             #+#    #+#             */
/*   Updated: 2019/07/19 13:18:29 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

unsigned int		reverse_bytes(unsigned int num)
{
	num = (num & 0x00FF00FF) << 8 | (num & 0xFF00FF00) >> 8;
	num = (num & 0x0000FFFF) << 16 | (num & 0xFFFF0000) >> 16;
	return (num);
}

void				carr_push_front(t_carriage **carr, t_player *pl)
{
	t_carriage *new;

	if (!(new = (t_carriage *)malloc(sizeof(t_carriage))))
		return ;
	ft_bzero((void *)new->reg, sizeof(int) * REG_NUMBER);
	new->pl = pl->num;
	new->alive = 0;
	new->reg[0] = -(pl->num);
	new->pos = 0;
	new->cycles = 0;
	new->carry = 0;
	new->is_dead = 0;
	new->next = NULL;
	if (!*carr)
	{
		*carr = new;
		return ;
	}
	new->next = *carr;
	*carr = new;
}

void				init_carriage(t_vm **vm)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if ((*vm)->players[i])
			carr_push_front(&((*vm)->carr), (*vm)->players[i]);
		i++;
	}
	(*vm)->last_live = (*vm)->players[(*vm)->carr->pl - 1];
}

void				swap_bytes(void *p, size_t s)
{
	char	*ptr;
	char	tmp;
	size_t	l;
	size_t	h;

	ptr = (char *)p;
	l = 0;
	h = s - 1;
	while (h > l)
	{
		tmp = ptr[l];
		ptr[l] = ptr[h];
		ptr[h] = tmp;
		l++;
		h--;
	}
}
