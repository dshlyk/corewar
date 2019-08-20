/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:52:05 by lgigi             #+#    #+#             */
/*   Updated: 2019/04/09 13:59:44 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	unsigned long	res;
	int				sign;
	char			*s;
	unsigned long	cutoff;

	res = 0;
	s = (char *)str;
	while (*s == ' ' || *s == '\t' || *s == '\n' \
			|| *s == '\r' || *s == '\v' || *s == '\f')
		s++;
	cutoff = 922337203685477580L;
	sign = (*s == '-') ? -1 : 1;
	s += (*s == '-' || *s == '+') ? 1 : 0;
	while (*s >= '0' && *s <= '9')
	{
		if (res >= cutoff || (res == cutoff && (((*s - '0') > 7 && sign == 1) \
						|| ((*s - '0') > 8 && sign == -1))))
		{
			res = (sign == -1) ? -9223372036854775808U : 9223372036854775807L;
			return ((int)res);
		}
		res = res * 10 + *s - '0';
		s++;
	}
	return ((int)res * sign);
}
