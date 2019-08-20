/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:15:43 by lgigi             #+#    #+#             */
/*   Updated: 2019/04/26 13:21:36 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*parse_flags(t_pr **val, char *fmt)
{
	char	flags[10];
	int		i;

	i = 0;
	ft_bzero((void *)flags, 10);
	if (ft_isconv(*fmt) || !*fmt ||\
		*fmt == '*' || (*fmt >= '1' && *fmt <= '9'))
		return (fmt);
	while (ft_isflag(*fmt) && i < 10 && *fmt)
	{
		flags[i++] = *fmt;
		fmt++;
	}
	if (ft_strchr(flags, '-'))
		(*val)->m_f |= F_MS;
	if (ft_strchr(flags, '#'))
		(*val)->m_f |= F_DSH;
	if (ft_strchr(flags, '+'))
		(*val)->m_f |= F_PL;
	if (ft_strchr(flags, '0') && !ft_strchr(flags, '-'))
		(*val)->m_f |= F_ZR;
	if (ft_strchr(flags, ' ') && !ft_strchr(flags, '+'))
		(*val)->m_f |= F_SP;
	return (fmt);
}

static char	*parse_pr_fl(t_pr **v, char *fmt, va_list ag)
{
	if (ft_isdigit(fmt[0]))
	{
		(*v)->field = ft_atoi(fmt);
		while (ft_isdigit(*fmt) && *fmt)
			fmt++;
	}
	if (*fmt == '*')
	{
		if (((*v)->field = va_arg(ag, int)) < 0)
		{
			(*v)->field = (*v)->field * -1;
			(*v)->m_f |= F_MS;
		}
		fmt++;
	}
	if (*fmt == '.' && *(fmt + 1) != '*')
		if (((*v)->prec = ft_atoi(fmt + 1)) <= 0)
			(*v)->prec = 0;
	if (*fmt == '.' && *(fmt + 1) == '*')
	{
		(*v)->m_f |= F_STR;
		(*v)->prec = va_arg(ag, int);
	}
	return (fmt);
}

char		*parse_val(t_pr **val, char *fmt, va_list ag)
{
	fmt = parse_flags(val, fmt);
	fmt = parse_pr_fl(val, fmt, ag);
	while (*fmt)
	{
		(*val)->m_f = (*fmt == 'l') ? (*val)->m_f | M_L : (*val)->m_f;
		(*val)->m_f = (*fmt == 'h' && \
						*(fmt + 1) == 'h') ? (*val)->m_f | M_HH : (*val)->m_f;
		(*val)->m_f = (*fmt == 'h' && *(fmt + 1) != 'h' \
						&& *(fmt - 1) != 'h') ? (*val)->m_f | M_H : (*val)->m_f;
		(*val)->m_f = (*fmt == 'L') ? (*val)->m_f | M_FL : (*val)->m_f;
		(*val)->m_f = (*fmt == 'z') ? (*val)->m_f | M_Z : (*val)->m_f;
		(*val)->m_f = (*fmt == 'j') ? (*val)->m_f | M_J : (*val)->m_f;
		if (ft_isconv(*fmt))
			break ;
		fmt++;
	}
	if (((*val)->m_f & F_STR) && (*val)->prec < 0)
		(*val)->prec = (*fmt == 's') ? -1 : 0;
	(*val)->m_f = ((*fmt == 'X' || *fmt == 'd' || *fmt == 'x' || \
	*fmt == 'i' || *fmt == 'o') && (*val)->prec != -1) ? \
						(*val)->m_f & ~F_ZR : (*val)->m_f;
	return (fmt);
}
