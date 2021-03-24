/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 08:29:45 by smaccary          #+#    #+#             */
/*   Updated: 2019/11/24 18:28:36 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strrchr(const char *s, int c)
{
	unsigned char *src;
	unsigned char *ptr;

	ptr = 0;
	src = (unsigned char *)s;
	c = (unsigned char)c;
	while (*src)
	{
		if (c == *src)
			ptr = src;
		src++;
	}
	return ((c == 0) ? (char *)src : (char *)ptr);
}
