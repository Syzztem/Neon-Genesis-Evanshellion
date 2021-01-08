/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbegin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:16:25 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/07 15:36:22 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strbegin(const char *str, const char *begin)
{
	size_t	i;

	i = 0;
	while (begin[i] && str[i] && begin[i] == str[i])
		i++;
	if (!begin[i])
		return (1);
	return (0);
}
