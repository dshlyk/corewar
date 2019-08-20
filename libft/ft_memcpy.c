/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:01:47 by lgigi             #+#    #+#             */
/*   Updated: 2019/04/05 17:35:23 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *cs;
	unsigned char *cd;

	cs = (unsigned char *)src;
	cd = (unsigned char *)dst;
	while (n--)
		*cd++ = *cs++;
	return (dst);
}
