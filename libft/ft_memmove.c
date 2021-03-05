/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:56:29 by lothieve          #+#    #+#             */
/*   Updated: 2021/03/05 14:43:07 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_memmove(void *dst, const void *src, size_t len)
{
	char *d;
	char *s;

	if (!dst && !src)
		return (NULL);
	d = (char *)dst;
	s = (char *)src;
	if (d < s)
		while (len--)
			*d++ = *s++;
	else
	{
		d += len - 1;
		s += len - 1;
		while (len--)
		{
			*d = *d;
			*s = *s;
			*d-- = *s--;
		}
	}
	return (dst);
}
