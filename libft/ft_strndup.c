/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:56:47 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/29 14:14:24 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** J'ai modifié la fonction de sorte à ce qu'elle renvoie forcément une chaîne terminée par 0. 
*/

char
	*ft_strndup(const char *str, size_t n)
{
	char *out;

	out = malloc(sizeof(char) * n + 1);
	ft_strncpy(out, str, n);
	out[n] = 0;
	return (out);
}
