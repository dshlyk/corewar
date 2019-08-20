/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_diox.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:44:29 by lgigi             #+#    #+#             */
/*   Updated: 2019/04/26 13:52:48 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long				arg_convert(va_list ag, t_pr *v)
{
	long n;

	if (!(v->m_f & M_Z) && !(v->m_f & M_J))
		n = (v->m_f & M_L) ? va_arg(ag, long) : va_arg(ag, int);
	else if ((v->m_f & M_Z) && !(v->m_f & M_J))
		n = va_arg(ag, size_t);
	else if (!(v->m_f & M_Z) && (v->m_f & M_J))
		n = va_arg(ag, intmax_t);
	n = (v->m_f & M_HH) ? (char)n : n;
	n = (v->m_f & M_H) ? (short)n : n;
	return (n);
}

static unsigned long	uns_arg_convert(va_list ag, t_pr *v, char conv)
{
	unsigned long n;

	if (!(v->m_f & M_Z) && !(v->m_f & M_J))
		n = (v->m_f & M_L || conv == 'U') ? va_arg(ag, unsigned long) \
								: va_arg(ag, unsigned int);
	else if ((v->m_f & M_Z) && !(v->m_f & M_J))
		n = va_arg(ag, ssize_t);
	else if (!(v->m_f & M_Z) && (v->m_f & M_J))
		n = va_arg(ag, uintmax_t);
	n = (v->m_f & M_HH && conv != 'U') ? (unsigned char)n : n;
	n = (v->m_f & M_H && conv != 'U') ? (unsigned short)n : n;
	return (n);
}

static void				add_pref(char mod, t_pr *v, long n, char *num)
{
	if ((v->m_f & F_DSH) && n != 0)
	{
		if (mod == 'o' && \
			!(v->prec > (int)ft_strlen(num)))
			ft_add_c('0', v);
		else if (mod == 'x')
		{
			ft_add_c('0', v);
			ft_add_c('x', v);
		}
		else if (mod == 'X')
		{
			ft_add_c('0', v);
			ft_add_c('X', v);
		}
	}
}

void					ft_print_i(va_list ag, t_pr *v, long i, char conv)
{
	long	n;
	char	*num;
	char	*tmp;

	n = arg_convert(ag, v);
	num = init_num_string(n, 0, v, conv);
	i = find_add_field_size(v, n, num, conv);
	if ((v->m_f & F_PL) && (v->m_f & F_ZR) && n >= 0 && v->prec == -1)
		ft_add_c('+', v);
	if ((v->m_f & F_SP) && ((v->m_f & F_MS) || (v->m_f & F_ZR)) && n >= 0)
		ft_add_c(' ', v);
	if ((v->m_f & F_ZR) && n < 0 && v->prec == -1)
		ft_add_c('-', v);
	if (!(v->m_f & F_MS))
		((v->m_f & F_ZR) && v->prec == -1) ? \
				ft_fill_buff(i, '0', v) : ft_fill_buff(i, ' ', v);
	manage_fl_prec(v, num, n, conv);
	tmp = ((n < 0 && v->prec > 0) || (n < 0 && \
						(v->m_f & F_ZR) && v->prec == -1)) ? num + 1 : num;
	while (*tmp && tmp)
		ft_add_c(*tmp++, v);
	if ((v->m_f & F_MS))
		ft_fill_buff(i, ' ', v);
	free(num);
}

void					ft_print_ox(va_list ag, t_pr *v, long i, char conv)
{
	unsigned long	n;
	char			*num;
	char			*tmp;

	n = uns_arg_convert(ag, v, conv);
	num = init_num_string(0, n, v, conv);
	i = (n != 0) ? find_add_field_size(v, 1, num, conv) : \
							find_add_field_size(v, n, num, conv);
	if ((v->m_f & F_PL) && (v->m_f & F_ZR) && v->prec == -1)
		ft_add_c(' ', v);
	if (!(((v->prec - (int)ft_strlen(num) > 0) || (i >= 0 && !(v->m_f & F_ZR)) \
		|| (i > 0 && v->prec >= 0)) && !(v->m_f & F_MS)))
		add_pref(conv, v, n, num);
	if (!(v->m_f & F_MS))
		((v->m_f & F_ZR) && v->prec == -1) ? \
							ft_fill_buff(i, '0', v) : ft_fill_buff(i, ' ', v);
	if (!(v->m_f & F_MS) && !(v->m_f & F_ZR))
		add_pref(conv, v, n, num);
	manage_fl_prec(v, num, n, conv);
	tmp = num;
	while (*tmp && tmp)
		ft_add_c(*tmp++, v);
	if ((v->m_f & F_MS))
		ft_fill_buff(i, ' ', v);
	free(num);
}
