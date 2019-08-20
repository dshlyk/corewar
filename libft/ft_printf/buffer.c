/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:09:12 by lgigi             #+#    #+#             */
/*   Updated: 2019/04/26 13:10:09 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_fill_buff(long i, char c, t_pr *v)
{
	while (i--)
		ft_add_c(c, v);
}

void	ft_add_c(int c, t_pr *v)
{
	if (v->index + 1 == BUF_S)
	{
		v->print += write(1, v->b, v->index);
		v->index = 0;
	}
	*(v->b + v->index++) = c;
}
