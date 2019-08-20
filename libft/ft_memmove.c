/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:03:30 by lgigi             #+#    #+#             */
/*   Updated: 2019/04/05 18:35:31 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*cs;
	char	*cd;
	size_t	i;

	i = 0;
	cs = (char *)src;
	cd = (char *)dst;
	if (cd == cs)
		return ((void *)src);
	if (cd < cs || cd >= (cs + n))
	{
		while (i < n)
		{
			cd[i] = cs[i];
			i++;
		}
	}
	else
	{
		while (n--)
			cd[n] = cs[n];
	}
	return (dst);
}
