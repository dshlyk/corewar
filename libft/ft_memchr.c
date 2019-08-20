/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 12:58:06 by lgigi             #+#    #+#             */
/*   Updated: 2019/04/03 12:58:29 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *str;

	if (n != 0)
	{
		str = (unsigned char *)s;
		while (n--)
		{
			if (*str == (unsigned char)c)
				return (str);
			str++;
		}
	}
	return (NULL);
}
