/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 11:47:34 by lothieve          #+#    #+#             */
/*   Updated: 2021/05/02 20:14:12 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

size_t
	count_chars(char *str, char *to_count)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		if (ft_strchr(to_count, *str))
			count++;
		str++;
	}
	return (count);
}

char
	*ft_strdup_escape(char *str, char quote)
{
	char	*new;
	size_t	i;
	char	*to_esc;

	to_esc = "";
	if (quote == '"')
		to_esc = TO_ESC_DB_QUOTE;
	else if (!quote)
		to_esc = TO_ESC_NO_QUOTE;
	new = ft_calloc(ft_strlen(str) + count_chars(str, to_esc) + 1, 1);
	i = 0;
	while (*str)
	{
		if (ft_strchr(to_esc, *str))
			new[i++] = '\\';
		new[i] = *str;
		i++;
		str++;
	}
	return (new);
}

static size_t
	add_env(char *command, char *quote, t_token **list)
{
	char *env;
	char *ref;

	ref = command;
	env = ft_lgetenv(++ref);
	if (env)
	{
		ft_lstadd_back((t_list **)list, ft_strdup_escape(env, *quote));
	}
	else if (*ref == '?')
	{
		ft_lstadd_back((t_list **)list, ft_itoa(g_exit_status));
		return (2);
	}
	while (ft_isalnum(*ref) || *ref == '_')
		++ref;
	return (ref - command);
}

void
	do_expansions(char **quote, char **ref, char *command, t_token **alst)
{
	size_t	len;

	if (!*(*quote) && (ft_strchr("\"'", *(*ref))
	&& ((*ref) == command || (*ref)[-1] != '\\')))
		(*quote) = (*ref);
	else if (*(*quote) == *(*ref))
		(*quote) = "\0";
	len = wildcard_len((*ref));
	if (len && *(*quote) != '\'')
		(*ref) += add_wildcard((*ref), len, alst);
	else if (*(*quote) != '\'' && *(*ref) == '$'
	&& ((*ref) == command || (*ref)[-1] != '\\') && **quote != '\'')
		(*ref) += add_env((*ref), *quote, alst);
	else
		ft_lstadd_back((t_list **)alst, ft_strndup((*ref)++, 1));
}

char
	*perform_expansions(char *command)
{
	t_token *list;
	char	*ref;
	char	*out;
	char	*quote;

	if (!command)
		return (NULL);
	ref = command;
	list = NULL;
	quote = "\0";
	while (*ref)
		do_expansions(&quote, &ref, command, &list);
	out = list_to_pure_string(list);
	free_list(list);
	return (out);
}

/*
** char
** 	*perform_expansions(char *command)
** {
** 	t_token *list;
** 	char	*ref;
** 	size_t	len;
** 	char	*out;
** 	char	*quote;
**
** 	if (!command)
** 		return (NULL);
** 	ref = command;
** 	list = NULL;
** 	quote = "\0";
** 	while (*ref)
** 	{
** 		if (!*quote && (ft_strchr("\"'", *ref)
** 		&& ref != command && ref[-1] != '\\'))
** 			quote = ref;
** 		else if (*quote == *ref)
** 			quote = "\0";
** 		len = wildcard_len(ref);
** 		if (len && *quote != '\'')
** 			ref += add_wildcard(ref, len, &list);
** 		else if (*quote != '\'' && *ref == '$'
** 		&& (ref == command || ref[-1] != '\\'))
** 			ref += add_env(ref, &list);
** 		else
** 			ft_lstadd_back((t_list **)&list, ft_strndup(ref++, 1));
** 	}
** 	out = list_to_pure_string(list);
** 	free_list(list);
** 	return (out);
** }
*/
