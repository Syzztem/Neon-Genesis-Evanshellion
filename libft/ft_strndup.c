/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:56:47 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/30 21:04:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_strndup(const char *str, size_t n)
{
	char *out;

	out = malloc(sizeof(char) * n + 1);
	ft_strncpy(out, str, n);
	out[n] = 0;
	return (out);
}
