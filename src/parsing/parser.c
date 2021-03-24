/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:16:41 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/24 13:56:13 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

t_pipeline
	parse_pipeline(char **tokens)
{
	t_command	*command;
	t_list		*lst;

	lst = NULL;
	while ((command = get_next_command(tokens)))
		ft_lstadd_back(&lst, command);
	get_next_command(NULL);
	return (lst);
}

size_t
	count_avoided_tokens(char **tokens)
{
	size_t	count;

	count = 0;
	while (*tokens)
	{
		if (is_redirect(*tokens))
			count += 2;
		tokens++;
	}
	return (count);
}

/*
** Extracts redirections and their arguments and returns them in a char **
** -> {">", "arg1", "<", "arg2", ">>", "arg3"}
*/

char
	**extract_redirects(char **tokens)
{
	char	**extracted;
	size_t	i;

	i = 0;
	extracted = ft_calloc(count_avoided_tokens(tokens) + 2, sizeof(char *));
	if (!extracted)
		return (NULL);
	while (*tokens)
	{
		if (is_redirect(*tokens))
		{
			extracted[i] = *tokens;
			if (*(tokens + 1))
				extracted[++i] = *(++tokens);
			i++;
		}
		tokens++;
	}
	return (extracted);
}

/*
** Return tokens without redirections and their arguments
*/

char
	**get_pure_tokens(char **tokens)
{
	char	**pure_tokens;
	char	**extracted;
	char	**current;
	size_t	i;

	i = 0;
	current = tokens;
	extracted = extract_redirects(tokens);
	pure_tokens = ft_calloc(pure_tokens_len(tokens, extracted) + 2,
	sizeof(char *));
	while (*current)
	{
		if (ref_in_tokens(*current, extracted) == 0)
		{
			pure_tokens[i] = *current;
			i++;
		}
		current++;
	}
	return (pure_tokens);
}

int
	open_output(char **output_path_ptr)
{
	int	open_mode;
	int	redir_type;
	int open_flags;

	redir_type = 0;
	open_flags = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	open_mode = O_WRONLY | O_CREAT;
	redir_type |= (int)ft_strlen(*output_path_ptr);
	if (redir_type == 1)
		open_mode |= O_TRUNC;
	else if (redir_type == 2)
		open_mode |= O_APPEND;
	return (open(output_path_ptr[1], open_mode, open_flags));
}
