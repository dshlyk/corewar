/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 12:52:50 by lgigi             #+#    #+#             */
/*   Updated: 2019/04/03 12:53:42 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(int n)
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

char		*ft_itoa(int n)
{
	char	*arr;
	int		size;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
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
