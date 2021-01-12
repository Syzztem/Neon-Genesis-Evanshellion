/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:37:48 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/12 13:38:55 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstmerge(t_list **begin_list1, t_list *begin_list2)
{
	t_list *elem;

	if (!*begin_list1)
	{
		*begin_list1 = begin_list2;
		return ;
	}
	elem = *begin_list1;
	while (elem->next)
		elem = elem->next;
	elem->next = begin_list2;
}
