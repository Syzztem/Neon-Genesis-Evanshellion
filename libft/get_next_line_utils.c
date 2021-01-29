/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 16:37:22 by smaccary          #+#    #+#             */
/*   Updated: 2021/01/29 15:32:58 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

size_t	gnl_ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*gnl_ft_strdup(const char *s1)
{
	char		*str;
	size_t		i;

	if (!(str = malloc(sizeof(char) * (gnl_ft_strlen(s1) + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

size_t	gnl_ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t srclen;
	size_t n;

	srclen = gnl_ft_strlen(src);
	n = srclen + 1;
	if (n < dstsize)
		while (n--)
			*(char *)(dest + n) = *(char *)(src + n);
	else if (dstsize != 0)
	{
		n = dstsize - 1;
		while (n--)
			*(char *)(dest + n) = *(char *)(src + n);
		dest[dstsize - 1] = '\0';
	}
	return (srclen);
}
	#include <stdio.h>


char	*gnl_ft_strndup(const char *s1, long long n)
{
	char	*str;
	size_t	i;

	if (n <= 0)
		return (gnl_ft_strdup(""));
	if (!(str = malloc(sizeof(char) * (n + 1))))
		return (NULL);
	i = 0;
	while (s1[i] && (long long)i < n)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*
** lens : {s1_len, s2_len}
*/

char	*gnl_ft_strjoin(char *s1, char *s2)
{
	char	*dst;
	size_t	lens[2];

	if (!s1 || !s2)
		return ((s1) ? gnl_ft_strdup(s1) : gnl_ft_strdup(s2));
	lens[0] = gnl_ft_strlen(s1);
	lens[1] = gnl_ft_strlen(s2);
	if (!(lens[0] + lens[1]))
		return (gnl_ft_strdup(""));
	if (!lens[0] || !lens[1])
		return ((!lens[0]) ? gnl_ft_strdup(s2) : gnl_ft_strdup(s1));
	if (!(dst = malloc(sizeof(char) * (lens[0] + lens[1] + 1))))
		return (NULL);
	gnl_ft_strlcpy(dst, s1, lens[0] + 1);
	gnl_ft_strlcpy(dst + lens[0], s2, lens[1] + 1);
	return (dst);
}
