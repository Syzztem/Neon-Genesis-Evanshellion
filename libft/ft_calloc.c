/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:25:24 by lothieve          #+#    #+#             */
/*   Updated: 2019/11/09 20:13:46 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void *out;

	if (count * size == 0)
		return (ft_strdup(""));
	if (!(out = malloc(count * size)))
		return (NULL);
	return (ft_bzero(out, count * size));
}
