/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randstring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:11:51 by lothieve          #+#    #+#             */
/*   Updated: 2019/11/06 14:25:56 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <unistd.h>
#include "libft.h"

char	*ft_randstring(int size)
{
	char	*str;
	char	c;
	int		i;

	srand(time(NULL));
	if (!(str = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		c = rand();
		str[i] = (c == 0 ? 1 : c);
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_prandstring(int size)
{
	char	*str;
	char	c;
	int		i;

	srand(time(NULL));
	if (!(str = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		c = rand();
		while (!ft_isprint(c))
			c = rand();
		str[i] = c;
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	*ft_randmem(int size)
{
	char	*str;
	char	c;
	int		i;

	srand(time(NULL));
	if (!(str = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		c = rand();
		str[i] = c;
		i++;
	}
	str[i] = '\0';
	return (str);
}
