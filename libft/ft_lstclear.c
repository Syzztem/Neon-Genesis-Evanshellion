/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:51:15 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/25 19:58:22 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *current;
	t_list	*next;

	current = *lst;
	*lst = NULL;
	while (current)
	{
		next = current->next;
		del(current->content);
		free(current);
		current = next;
	}
}
