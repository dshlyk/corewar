/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_fl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:22:15 by lgigi             #+#    #+#             */
/*   Updated: 2019/04/26 13:33:09 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long	double	arg_fl_convert(va_list ag, t_pr *v)
{
	long double n;

	n = (v->m_f & M_FL) ? va_arg(ag, long double) : va_arg(ag, double);
	return (n);
}

static char			*fill_float_str(long double n,
					char *s, t_pr *v, unsigned int size)
{
	long double	swp;
	long		expon;
	char		*p;
	int			round;

	while (v->prec--)
	{
		swp = n;
		n *= (long double)10.0f;
		n -= (long)swp * 10.0;
		expon = (v->prec == 0 && (((long)(n * 10.0f) % 10) > 4)) \
											? (long)n + 1 : (long)n;
		round = (expon > 9) ? 1 : 0;
		if (!(p = (expon > 9) ? ft_itoa(0) : ft_itoa(expon)))
			exit(1);
		s[size++] = *p;
		free(p);
	}
	return ((round) ? rounder(size - 2, size - 2, s, round) : s);
}

static char			*find_exp(long double n,
					unsigned int size, unsigned int i, long expon)
{
	char			*s;
	char			*p;

	while ((long)n != 0)
	{
		n /= 10;
		size++;
	}
	if (size == 0)
		return (ft_strdup("0"));
	s = ft_strnew(size + 1);
	while (size--)
	{
		n *= (long double)100.0f;
		expon = (long)(n / 10.0);
		n -= (long)expon * 10;
		n /= 10;
		if (!(p = ft_itoa(expon)))
			exit(1);
		*(s + i++) = *p;
		free(p);
	}
	return (s);
}

static char			*init_float_str(long double n, t_pr *v, int size)
{
	char		*expn;
	char		*s;

	if (n == 1.0 / 0.0 || n == -1.0 / 0.0 || n != n)
	{
		v->prec = 0;
		return ((n != n) ? ft_strdup("-nan") \
							: ft_strdup("inf"));
	}
	n = (n < 0) ? -n : n;
	expn = find_exp(n, 0, 0, 0);
	size = ft_strlen(expn);
	if (!v->prec && ((long)(n * 10.00) % 10) >= 5 \
	&& (((long)n % 10) >= 5 || ((long)(n * 100.00) % 10) >= 1))
		expn = rounder(size, size, expn, 2);
	if (!v->prec && !(v->m_f & F_DSH))
		return (expn);
	v->prec = (v->prec == -1) ? 6 : v->prec;
	s = ft_strcpy(ft_strnew(size + v->prec + 1), expn);
	s[size++] = '.';
	free(expn);
	if (!v->prec && (v->m_f & F_DSH))
		return (s);
	return ((!v->prec) ? s : fill_float_str(n, s, v, size));
}

void				print_float(va_list ag, t_pr *v, long i, char conv)
{
	long double		n;
	char			*num;
	char			*tmp;

	n = arg_fl_convert(ag, v);
	num = init_float_str(n, v, 0);
	i = (n < 0) ? find_add_field_size(v, -1, num, conv) : \
					find_add_field_size(v, (long)n, num, conv);
	i += ((n != n || n == 1.0 / 0.0) && v->field > (int)ft_strlen(num)) ? 1 : 0;
	if (((v->m_f & F_ZR) || !i || (v->m_f & F_MS)) && (v->m_f & F_PL) && n >= 0)
		ft_add_c('+', v);
	if (((v->m_f & F_ZR) || i == 0 || (v->m_f & F_MS)) \
						&& (v->m_f & F_SP) && n >= 0)
		ft_add_c(' ', v);
	if (((v->m_f & F_ZR) || i == 0 || (v->m_f & F_MS)) && n < 0)
		ft_add_c('-', v);
	if (!(v->m_f & F_MS))
		((v->m_f & F_ZR)) ? ft_fill_buff(i, '0', v) : ft_fill_buff(i, ' ', v);
	manage_flags(i, v, n);
	tmp = num;
	while (*tmp && tmp)
		ft_add_c(*tmp++, v);
	if ((v->m_f & F_MS))
		ft_fill_buff(i, ' ', v);
	free(num);
}
