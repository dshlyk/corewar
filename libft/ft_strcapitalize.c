/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 15:50:32 by lgigi             #+#    #+#             */
/*   Updated: 2019/04/05 10:47:21 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcapitalize(char *str)
{
	int		inword;
	size_t	i;

	i = 0;
	inword = 0;
	while (str[i])
	{
		str[i] += (str[i] >= 'A' && str[i] <= 'Z') ? 32 : 0;
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (!inword && ((str[i] >= 'a' && str[i] <= 'z') \
					|| (str[i] >= '0' && str[i] <= '9')))
		{
			inword = 1;
			str[i] -= (str[i] >= 'a' && str[i] <= 'z') ? 32 : 0;
		}
		else if (inword && !(str[i] >= 'a' && str[i] <= 'z') \
				&& !(str[i] >= '0' && str[i] <= '9'))
			inword = 0;
		i++;
	}
	return (str);
}
