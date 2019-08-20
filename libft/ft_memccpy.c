/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 12:56:36 by lgigi             #+#    #+#             */
/*   Updated: 2019/04/05 17:35:04 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char *cs;
	unsigned char *cd;

	cs = (unsigned char *)src;
	cd = (unsigned char *)dst;
	while (n--)
	{
		*cd = *cs;
		if (*cs == (unsigned char)c)
			return ((void *)(cd + 1));
		cd++;
		cs++;
	}
	return (NULL);
}
