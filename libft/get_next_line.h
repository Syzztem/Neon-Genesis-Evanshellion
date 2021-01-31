/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 14:53:19 by smaccary          #+#    #+#             */
/*   Updated: 2019/12/10 21:02:10 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

typedef	struct		s_gnl_list
{
	int				fd;
	char			*rest;
	struct s_gnl_list	*next;
}					t_gnl_list;

int					get_next_line(int fd, char **line);
size_t				gnl_ft_strlcpy(char *dest, const char *src, size_t dstsize);
char				*gnl_ft_strdup(const char *s1);
size_t				gnl_ft_strlen(const char *str);
char				*gnl_ft_strndup(const char *s4, long long n);
char				*gnl_ft_strjoin(char *s1, char *s2);
#endif
