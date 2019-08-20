/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 11:09:24 by lgigi             #+#    #+#             */
/*   Updated: 2019/04/05 15:01:35 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst,
					void (*del)(void *, size_t))
{
	t_list *temp;

	if (!del)
		return ;
	while (*alst != NULL)
	{
		temp = *alst;
		*alst = (*alst)->next;
		ft_lstdelone(&temp, del);
	}
}
