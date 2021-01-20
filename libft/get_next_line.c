/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:08:54 by lnoirot           #+#    #+#             */
/*   Updated: 2021/01/20 15:10:44 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

static int		ft_search_line(char *buff, unsigned int i)
{
	unsigned int j;

	j = 0;
	while (j < BUFFER_SIZE - i)
	{
		if (buff[j] == '\n')
			return (1);
		j++;
	}
	return (0);
}

static char		*ft_strjoin_line(char *s1, char *s2, unsigned int i)
{
	char			*r;
	unsigned int	j;
	unsigned int	len2;
	unsigned int	len1;

	j = 0;
	len1 = 0;
	len2 = 0;
	while (s1[len1])
		len1++;
	while (len2 < BUFFER_SIZE - i)
		len2++;
	if (!(r = (char *)malloc(sizeof(char)
					* (len1 + len2 + 1))))
		return (NULL);
	while (*s1 && *s1 != '\n')
		r[j++] = *s1++;
	while (j < len1 + len2 && *s2 != '\n')
		r[j++] = *s2++;
	r[j] = '\0';
	return (r);
}

static char		*ft_strdup_line(char *buff, unsigned int i)
{
	char			*str;
	unsigned int	j;
	unsigned int	len;

	j = 0;
	len = 0;
	while (len < BUFFER_SIZE - i && buff[len] != '\n')
		len++;
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (j < len)
	{
		str[j] = buff[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

static int		fill_the_line(char *buff, unsigned int *i, int fd, char **line)
{
	char *tmp;

	tmp = *line;
	if (!(*line = ft_strdup_line(&buff[*i], *i)))
		return (-1);
	free(tmp);
	while (ft_search_line(&buff[*i], *i) == 0)
	{
		ft_bzero(buff, BUFFER_SIZE);
		*i = 0;
		if (!(read(fd, buff, BUFFER_SIZE)))
			return (0);
		tmp = *line;
		*line = ft_strjoin_line(*line, buff, *i);
		free(tmp);
	}
	while (*i < BUFFER_SIZE && buff[*i] != '\n')
		(*i)++;
	if (*i < BUFFER_SIZE && buff[*i] == '\n')
		(*i)++;
	return (1);
}

int				get_next_line(int fd, char **line)
{
	static unsigned int		i = 0;
	static char				buff[BUFFER_SIZE];
	int						ret;

	ret = 0;
	if (i == BUFFER_SIZE || !line)
	{
		ft_bzero(buff, BUFFER_SIZE);
		i = 0;
	}
	if (!line)
		return (0);
	*line = ft_strdup_line("", BUFFER_SIZE - 1);
	if (i < BUFFER_SIZE && buff[i])
		return (ret = fill_the_line(buff, &i, fd, line));
	if (read(fd, buff, BUFFER_SIZE) < 0)
		return (-1);
	else
		return (ret = fill_the_line(buff, &i, fd, line));
	if (i != 0)
		*line = ft_strdup_line("", BUFFER_SIZE - 1);
	return (0);
}
