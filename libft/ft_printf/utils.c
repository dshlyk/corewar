/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:54:27 by lgigi             #+#    #+#             */
/*   Updated: 2019/04/26 13:58:31 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	manage_flags(long i, t_pr *v, long double n)
{
	if (i > 0 && !(v->m_f & F_ZR) && \
			!(v->m_f & F_MS) && (v->m_f & F_PL) && n >= 0)
		ft_add_c('+', v);
	if (i > 0 && !(v->m_f & F_ZR) && \
			!(v->m_f & F_MS) && (v->m_f & F_SP) && n >= 0)
		ft_add_c(' ', v);
	if (i > 0 && !(v->m_f & F_ZR) && \
					!(v->m_f & F_MS) && n < 0)
		ft_add_c('-', v);
}

void	manage_fl_prec(t_pr *v, char *num, long n, char conv)
{
	if ((v->m_f & F_PL) && !(v->m_f & F_ZR) && n >= 0 \
		&& conv != 'o' && conv != 'b' && conv != 'u' && \
		conv != 'x' && conv != 'X' && conv != 'U')
		ft_add_c('+', v);
	if (v->prec > 0 && n < 0 && conv != 'o' && conv != 'U'\
		&& conv != 'b' && conv != 'u' && conv != 'x' && conv != 'X')
		ft_add_c('-', v);
	if ((v->m_f & F_SP) && !(v->m_f & F_MS) && !(v->m_f & F_ZR)\
			&& n >= 0 && (conv == 'd' || conv == 'i'))
		ft_add_c(' ', v);
	if (v->prec > 0 && !(n == 0 && !v->prec) && (v->prec > (int)ft_strlen(num)))
		ft_fill_buff((v->prec - (int)ft_strlen(num)), '0', v);
	if (v->prec > 0 && !(n == 0 && !v->prec) && \
		(v->prec > (int)ft_strlen(num + 1) && n < 0))
		ft_add_c('0', v);
}

char	*rounder(int size, unsigned int sz,
							char *s, int round)
{
	char		*new;

	sz = size;
	if (round != 2)
		while (s[size] == '9')
			s[size--] = '0';
	if (s[size] == '.' || round == 2)
	{
		while (s[--size] == '9' && size)
			s[size] = '0';
		s[size] = (s[size] == '9') ? '0' : s[size];
		if (size <= 0 && s[size] == '0')
		{
			if (!(new = ft_strnew(sz + 1)))
				exit(1);
			new[0] = '1';
			ft_strcpy(new + 1, s);
			free(s);
			return (new);
		}
	}
	s[size]++;
	return (s);
}

long	find_add_field_size(t_pr *v, long n, char *num, char conv)
{
	long i;

	if (n < 0 && conv != 'f')
		i = v->field - MAX(v->prec + 1, ((int)ft_strlen(num)));
	else
		i = v->field - MAX(v->prec, ((int)ft_strlen(num)));
	i -= (((v->m_f & F_PL) || (v->m_f & F_SP)) && n >= 0 && conv != 'o' \
			&& conv != 'u' && conv != 'U' && conv != 'b' && \
			conv != 'x' && conv != 'X') ? 1 : 0;
	i -= (conv == 'f' && n < 0) ? 1 : 0;
	if (n != 0 && (v->m_f & F_DSH))
	{
		if (conv == 'o' && \
			!(v->prec > (int)ft_strlen(num)))
			i -= 1;
		else if (conv == 'x' || conv == 'X')
			i -= 2;
	}
	return ((i < 0) ? 0 : i);
}

char	*init_num_string(long n, unsigned long l, t_pr *v, char conv)
{
	char *num;

	num = NULL;
	if (conv == 'o')
		num = (l == 0 && !v->prec && !(v->m_f & F_DSH)) ? \
				ft_strnew(1) : ft_ultoa_base(l, 8, 0);
	else if (conv == 'x')
		num = (l == 0 && !v->prec) ? \
				ft_strnew(1) : ft_ultoa_base(l, 16, 0);
	else if (conv == 'b')
		num = (l == 0 && !v->prec) ? \
				ft_strnew(1) : ft_ultoa_base(l, 2, 0);
	else if (conv == 'X')
		num = (l == 0 && !v->prec) ? \
				ft_strnew(1) : ft_ultoa_base(l, 16, 1);
	else if (conv == 'u' || conv == 'U')
		num = (l == 0 && !v->prec) ? ft_strnew(1) : ft_ultoa(l);
	else if (conv == 'd' || conv == 'i')
		num = (n == 0 && !v->prec) ? ft_strnew(1) : ft_ltoa(n);
	if (num == NULL)
		exit(1);
	return (num);
}
