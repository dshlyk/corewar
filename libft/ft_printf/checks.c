/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:10:26 by lgigi             #+#    #+#             */
/*   Updated: 2019/04/26 15:45:25 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		mods_checker(char *fmt)
{
	while (*fmt && fmt)
	{
		if (!check_multipy_mods(fmt))
			return (0);
		if (!ft_isconv(*fmt) && !ft_isdigit(*fmt) \
				&& *fmt != '.' && *fmt != '*' \
				&& !ft_isflag(*fmt) && *fmt != 'l' && *fmt != 'h' \
				&& *fmt != 'z' && *fmt != 'j' && \
				*fmt != 'L' && ft_isalpha(*fmt))
			return (-2);
		if (ft_isconv(*fmt))
			break ;
		fmt++;
	}
	if (!*fmt)
		return (-1);
	return (1);
}

int		check_multipy_mods(char *f)
{
	if (*f == 'h' && *(f - 1) == 'h' && \
		(*(f + 1) == 'l' || *(f + 1) == 'L' \
		|| *(f + 1) == 'h' || *(f + 1) == 'z' \
		|| *(f + 1) == 'j'))
		return (0);
	if (*f == 'l' && *(f - 1) == 'l' && (*(f + 1) == 'l' \
		|| *(f + 1) == 'L' || *(f + 1) == 'h' \
		|| *(f + 1) == 'z' || *(f + 1) == 'j'))
		return (0);
	if (*f == 'l' && (*(f + 1) == 'L' || *(f + 1) == 'h' \
		|| *(f + 1) == 'z' || *(f + 1) == 'j'))
		return (0);
	if (*f == 'h' && (*(f + 1) == 'L' || *(f + 1) == 'l' \
		|| *(f + 1) == 'z' || *(f + 1) == 'j'))
		return (0);
	if (*f == 'L' && (*(f + 1) == 'h' || *(f + 1) == 'l' \
		|| *(f + 1) == 'z' || *(f + 1) == 'j'))
		return (0);
	if (*f == 'z' && (*(f + 1) == 'h' || *(f + 1) == 'l' \
		|| *(f + 1) == 'L' || *(f + 1) == 'j'))
		return (0);
	if (*f == 'j' && (*(f + 1) == 'h' || *(f + 1) == 'l' \
		|| *(f + 1) == 'L' || *(f + 1) == 'z'))
		return (0);
	return (1);
}

int		ft_isconv(char c)
{
	if (c == 'd' || c == 'i' || c == 'c' || c == 'u' || c == 'U'\
			|| c == 'x' || c == 's' || c == 'o' || c == 'f' \
			|| c == 'X' || c == 'p' || c == '%' || c == 'b')
		return (1);
	return (0);
}

int		ft_isflag(char c)
{
	return (c == ' ' || c == '0' || c == '+' \
					|| c == '-' || c == '#');
}
