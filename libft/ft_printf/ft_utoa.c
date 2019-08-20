/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:53:17 by lgigi             #+#    #+#             */
/*   Updated: 2019/04/26 13:54:07 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned long	get_size(unsigned long n, int base)
{
	unsigned long	size;

	size = 0;
	while (n)
	{
		size++;
		n /= base;
	}
	return (size);
}

char					*ft_utoa(unsigned int n)
{
	char			*arr;
	unsigned long	size;

	if (n == 0)
		return (ft_strdup("0"));
	size = get_size(n, 10);
	if (!(arr = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	arr[size] = '\0';
	while (n)
	{
		arr[--size] = n % 10 + '0';
		n /= 10;
	}
	return (arr);
}

char					*ft_ultoa(unsigned long n)
{
	char			*arr;
	unsigned long	size;

	if (n == 0)
		return (ft_strdup("0"));
	size = get_size(n, 10);
	if (!(arr = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	arr[size] = '\0';
	while (n)
	{
		arr[--size] = n % 10 + '0';
		n /= 10;
	}
	return (arr);
}

char					*ft_ultoa_base(unsigned long n, int base, int flag)
{
	char			*arr;
	unsigned long	size;

	if (n == 0)
		return (ft_strdup("0"));
	size = get_size(n, base);
	if (!(arr = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	arr[size] = '\0';
	while (n)
	{
		if (!flag)
			arr[--size] = (n % base > 9) ? n % base + 'a' - 10 :\
										n % base + '0';
		else
			arr[--size] = (n % base > 9) ? n % base + 'A' - 10 :\
										n % base + '0';
		n /= base;
	}
	return (arr);
}
