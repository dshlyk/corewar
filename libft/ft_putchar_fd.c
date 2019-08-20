/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:05:25 by lgigi             #+#    #+#             */
/*   Updated: 2019/04/09 13:59:16 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	unsigned char ch;
	unsigned char u[2];

	ch = (unsigned char)c;
	if (ch < 128)
		write(fd, &c, 1);
	else
	{
		u[0] = 192 | (ch >> 6);
		u[1] = 128 | (63 & ch);
		write(fd, u, 2);
	}
}
