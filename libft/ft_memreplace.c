/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:31:23 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/11 14:41:43 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memreplace(void *source, char a, char b, size_t size)
{
	char	*str;
	size_t	i;

	str = source;
	i = -1;
	while (++i < size)
		if (str[i] == a)
			str[i] = b;
	return (source);
}
