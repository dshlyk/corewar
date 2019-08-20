/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgigi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 11:40:35 by lgigi             #+#    #+#             */
/*   Updated: 2019/04/05 15:03:22 by lgigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*t;
	t_list	*list;

	if (!lst || !f)
		return (NULL);
	if (!(t = f(lst)))
		return (NULL);
	new = t;
	list = new;
	while (lst->next)
	{
		if (!(t = f(lst->next)))
		{
			if (new != NULL)
				free(new);
			return (NULL);
		}
		list->next = t;
		list = list->next;
		lst = lst->next;
	}
	return (new);
}
