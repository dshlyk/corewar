/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:36:39 by lgigi             #+#    #+#             */
/*   Updated: 2019/04/26 14:51:55 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_pr		*init_val(void)
{
	t_pr	*vals;

	if (!(vals = (t_pr *)malloc(sizeof(t_pr))))
		return (NULL);
	vals->prec = -1;
	vals->index = 0;
	vals->field = 0;
	vals->print = 0;
	vals->m_f = 0;
	ft_bzero((void *)vals->b, BUF_S);
	return (vals);
}

static void		clear_struct(t_pr **v)
{
	(*v)->prec = -1;
	(*v)->field = 0;
	(*v)->m_f = 0;
}

static int		ft_choices(char conv, va_list args, t_pr *vals)
{
	if (conv == 'c')
		ft_print_c(args, vals, 0);
	else if (conv == 'd' || conv == 'i')
		ft_print_i(args, vals, 0, conv);
	else if (conv == 'o' || conv == 'x' || conv == 'b' \
			|| conv == 'U' || conv == 'u' || conv == 'X')
		ft_print_ox(args, vals, 0, conv);
	else if (conv == 's')
		ft_print_str(args, vals);
	else if (conv == 'p')
		ft_print_ptr(args, vals, 0);
	else if (conv == 'f')
		print_float(args, vals, 0, conv);
	else if (conv == '%')
		ft_print_c(args, vals, 1);
	else
		return (-1);
	return (vals->print);
}

static int		pr_handler(char *str, long size, t_pr *vals, va_list args)
{
	if (*str == '\0' || !str || size == -1)
		return ((int)size);
	while (*str && *str != '%')
		ft_add_c(*str++, vals);
	if (*str == '%')
	{
		if (mods_checker(str + 1) == -1)
			return (0);
		if (mods_checker(str + 1) == -2)
			return (*(str + 2) ? pr_handler(str + 2, size, vals, args) : 0);
		if (!mods_checker(str + 1))
		{
			clear_struct(&vals);
			ft_add_c('%', vals);
			while (check_multipy_mods(str))
				str++;
			return (pr_handler(str + 1, size, vals, args));
		}
		str = parse_val(&vals, str + 1, args);
		size += ft_choices(*str, args, vals);
		vals->print = 0;
		str++;
	}
	clear_struct(&vals);
	return (pr_handler(str, size, vals, args));
}

int				ft_printf(const char *format, ...)
{
	t_pr	*vals;
	int		size;
	va_list arg;

	va_start(arg, format);
	if (!format)
		return (-1);
	if (!(vals = init_val()))
		return (-1);
	size = pr_handler((char *)format, 0, vals, arg);
	size += vals->print;
	if (vals->index)
		size += write(1, vals->b, vals->index);
	va_end(arg);
	free(vals);
	return ((int)size);
}
