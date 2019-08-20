/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_scp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:33:30 by lgigi             #+#    #+#             */
/*   Updated: 2019/04/26 14:16:39 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_c(va_list ag, t_pr *vals, int perc)
{
	int i;
	int c;

	i = 0;
	c = (perc) ? '%' : va_arg(ag, int);
	if (!(vals->m_f & F_MS))
	{
		while (++i < vals->field)
			ft_add_c(' ', vals);
		ft_add_c(c, vals);
	}
	else
	{
		ft_add_c(c, vals);
		while (++i < vals->field)
			ft_add_c(' ', vals);
	}
}

void	ft_print_str(va_list ag, t_pr *vals)
{
	char			*s;
	char			*tmp;
	int				i;

	i = 0;
	tmp = va_arg(ag, char *);
	if (!(s = (tmp) ? ft_strdup(tmp) : ft_strdup("(null)")))
		exit(1);
	if (vals->prec >= 0)
		s[vals->prec] = (vals->prec < (int)ft_strlen(s)) ?\
						'\0' : s[vals->prec];
	i = vals->field - (int)ft_strlen(s);
	if (i > 0 && !(vals->m_f & F_MS))
		ft_fill_buff(i, ' ', vals);
	tmp = s;
	while (*s && tmp && s)
		ft_add_c(*s++, vals);
	if ((vals->m_f & F_MS) && i > 0)
		ft_fill_buff(i, ' ', vals);
	((tmp) ? free(tmp) : free(s));
}

void	ft_print_ptr(va_list ag, t_pr *vals, long i)
{
	char	*s;
	void	*tmp;

	tmp = va_arg(ag, void *);
	if (!(s = (tmp) ? ft_ultoa_base((uintptr_t)tmp, 16, 0) \
									: ft_strdup("0x0")))
		exit(1);
	s[2] = (!tmp && !vals->prec) ? '\0' : s[2];
	i = (tmp) ? (vals->field - (MAX((int)ft_strlen(s), vals->prec) + 2)) :\
										vals->field - (int)ft_strlen(s);
	if (i > 0 && !(vals->m_f & F_MS))
		ft_fill_buff(i, ' ', vals);
	if (tmp)
	{
		ft_add_c('0', vals);
		ft_add_c('x', vals);
	}
	while (tmp && vals->prec-- > (int)ft_strlen(s))
		ft_add_c('0', vals);
	tmp = s;
	while (*s && s)
		ft_add_c(*s++, vals);
	if ((vals->m_f & F_MS) && i > 0)
		ft_fill_buff(i, ' ', vals);
	free(tmp);
}
