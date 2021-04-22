/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:16:41 by smaccary          #+#    #+#             */
/*   Updated: 2021/04/22 15:44:15 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

t_pipeline
	parse_pipeline(char **pipeline)
{
	t_command	*command;
	t_list		*lst;
	char		**tokens;

	lst = NULL;
	tokens = pipeline;
	//tokens = tokenize(pipeline);
	print_argv(pipeline);
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
				extracted[++i] = (*(++tokens));
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
	pure_tokens = ft_calloc(pure_tokens_len(tokens, extracted) + 3,
	sizeof(char *));
	while (*current)
	{
		if (ref_in_tokens(*current, extracted) == 0)
		{
			pure_tokens[i] = ft_strdup(*current);
			i++;
		}
		current++;
	}
	free(extracted);
	return (pure_tokens);
}
