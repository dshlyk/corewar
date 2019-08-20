/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:21:33 by lgigi             #+#    #+#             */
/*   Updated: 2019/04/09 12:35:13 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*d;
	const char	*s;
	size_t		dlen;
	size_t		slen;
	size_t		n;

	d = dst;
	s = src;
	n = size;
	slen = ft_strlen(s);
	while (*d != '\0' && n--)
		d++;
	dlen = d - dst;
	n = size - dlen;
	if (n == 0)
		return (dlen + slen);
	n -= 1;
	while (*s != '\0' && n--)
		*d++ = *s++;
	*d = '\0';
	return (dlen + slen);
}
