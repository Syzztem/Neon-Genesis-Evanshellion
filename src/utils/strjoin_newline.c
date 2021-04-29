/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_newline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 19:24:31 by user42            #+#    #+#             */
/*   Updated: 2021/04/29 19:24:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*strjoin_newline(char *s1, char *s2)
{
	char	*new;
	size_t	len_1;
	size_t	len_2;
	size_t	len;

	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	len = len_1 + len_2 + 1;
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	ft_memcpy(new, s1, len_1);
	new[len_1] = '\n';
	ft_memcpy(new + len_1 + 1, s2, len_2);
	new[len] = 0;
	return (new);
}
