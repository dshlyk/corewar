/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:14:52 by lgigi             #+#    #+#             */
/*   Updated: 2019/04/26 13:15:27 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	get_size(long n)
{
	int		size;

	size = (n < 0) ? 1 : 0;
	n = (n < 0) ? -n : n;
	while (n)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char			*ft_ltoa(long long n)
{
	char	*arr;
	size_t	size;

	if ((unsigned long)n == -9223372036854775808U)
		return (ft_strdup("-9223372036854775808"));
	else if (n == 0)
		return (ft_strdup("0"));
	size = get_size(n);
	if (!(arr = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	arr[size] = '\0';
	arr[0] = (n < 0) ? '-' : arr[0];
	n = (n < 0) ? -n : n;
	while (n)
	{
		arr[--size] = n % 10 + '0';
		n /= 10;
	}
	return (arr);
}
