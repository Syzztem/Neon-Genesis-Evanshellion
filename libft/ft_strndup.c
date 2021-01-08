/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:56:47 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/06 18:01:47 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_strndup(const char *str, size_t n)
{
	char *out;

	out = malloc(sizeof(char) * n);
	return (ft_strncpy(out, str, n));
}
