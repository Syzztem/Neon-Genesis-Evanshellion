/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:11:40 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/12 13:40:55 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
#include "get_next_line.h"

typedef struct	s_list
{
	struct s_list	*next;
	void			*content;
}				t_list;

int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isspace(int c);
int				ft_isprint(int c);
int				ft_tolower(int c);
int				ft_toupper(int c);
int				ft_indexof(const char *str, char c);
int				ft_atoi(const char *str);
int				ft_strbegin(const char *str, const char *begin);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_free_tab(char **tab);
void			*ft_bzero(void *s, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memreplace(void *source, char a, char b, size_t size);
void			*ft_calloc(size_t count, size_t size);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
char			*ft_itoa(int nbr);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			**ft_split(const char *str, char c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strnstr(const char *h, const char *n, size_t l);
char			*ft_strdup(const char *src);
char			*ft_strndup(const char *src, size_t n);
char			*ft_strncpy(char *dst, const char *src, size_t n);
char			*ft_strcat(char *dst, const char *src);
char			*ft_strcpy(char *dest, const char *src);
size_t			ft_putchar_fd(char c, int fd);
size_t			ft_putendl_fd(char *s, int fd);
size_t			ft_putnbr_fd(int nb, int fd);
size_t			ft_putstr_fd(char *s, int fd);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
size_t			ft_strlen(const char *str);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
t_list			*ft_lstnew(void *content);
t_list			*ft_lstmap(t_list *l, void *(*f)(void *), void (*del)(void *));
void			ft_lstmerge(t_list **first, t_list *second);
void			ft_lstadd_back(t_list **alst, void *new);
void			ft_lstadd_front(t_list **begin_list, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list *lst, void (*free_fct)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
int				ft_lstsize(t_list *lst);

#endif
