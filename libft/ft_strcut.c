/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 10:28:40 by lgigi             #+#    #+#             */
/*   Updated: 2019/04/05 10:48:38 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcut(char *str, int n)
{
	int		size;
	char	*res;

	if (!str)
		return (NULL);
	size = ft_strlen(str) - n;
	if (size < 0)
		return (NULL);
	if ((res = (char *)malloc(sizeof(char) * size + 1)) == NULL)
		return (NULL);
	res[size] = '\0';
	while (size--)
		res[size] = str[size];
	return (res);
}
