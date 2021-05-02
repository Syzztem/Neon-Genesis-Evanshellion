/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 21:08:43 by user42            #+#    #+#             */
/*   Updated: 2021/05/02 18:09:12 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "tokenizer.h"
#include "vector.h"

#include "tokenizer.h"

#include "minishell.h"
#include "minishell.h"
#include "parser.h"
#define SQ_ESCAPES " \t\n\v\f\r;&|\"*<>()\\$"
#define DQ_ESCAPES " \t\n\v\f\r;&|\'*<>()"
#define DQ_ESCAPES_2 " \t\n\v\f\r;&|*<>()"


static size_t
	next_space(char *command)
{
	char *ref;

	ref = command;
	while (*ref && ((!ft_isspace(*ref)
			|| (ref != command && *(ref - 1) == '\\'))))
		++ref;
	return (ref - command);
}

static size_t
	next_token(char *command)
{
	char *ref;

	ref = command;
	while (ft_isspace(*ref) && (ref == command || *(ref - 1) != '\\'))
		++ref;
	return (ref - command);
}

static size_t
	tok_count(char *command)
{
	size_t	count;

	count = 1;
	while (*command)
	{
		command += next_token(command);
		command += next_space(command);
		++count;
	}
	return (count);
}

static void
	clean_backslashes(char **tokens)
{
	char	*line;
	char	*found;

	while (*tokens)
	{
		line = *tokens;
		while (*line)
		{
			if (*line == '\x1b')
			{
				ft_memmove(line, line + 1, ft_strlen(line));
				continue;
			}
			found = ft_strchr(SQ_ESCAPES "'", line[1]);
			if (*line == '\\' && found && *found)
				ft_memmove(line, line + 1, ft_strlen(line));
			++line;
		}
		++tokens;
	}
}

char
	**tokenize(char *command, char *end)
{
	char	**out;
	size_t	i;
	size_t	next;

	out = ft_calloc((tok_count(command) + 1), sizeof(char *));
	i = 0;
	while (command < end)
	{
		command += next_token(command);
		next = next_space(command);
		if (!next)
			continue ;
		out[i] = ft_strndup(command, next);
		command += next;
		++i;
	}
	out[i] = NULL;
	clean_backslashes(out);
	return (out);
}

size_t
	argv_len(char **argv)
{
	char	**current;

	current = argv;
	while (*current)
		current++;
	return (current - argv);
}

char
	**dequote_tokens(char **tokens)
{
	char	*dequoted;
	char	**new;
	size_t	i;

	new = ft_calloc(argv_len(tokens) + 1, sizeof(char **));
	i = 0;
	while (tokens[i])
	{
		dequoted = remove_quotes(tokens[i]);
		new[i] = dequoted;
		i++;
	}
	return (new);
}

char
	**expand_and_dequote_tokens(char **tokens)
{
	char	*expanded;
	char	*dequoted;
	char	**new;
	size_t	i;

	new = ft_calloc(argv_len(tokens) + 1, sizeof(char **));
	i = 0;
	while (tokens[i])
	{
		expanded = perform_expansions(tokens[i]);
		dequoted = remove_quotes(expanded);
		free(expanded);
		new[i] = dequoted;
		i++;
	}
	return (new);
}


 char
 	*remove_quotes_a(char *line, char **end)
 {
 	char	*current;
 	char	*quote;
 	int		escaped;
 	char	*new;
 	size_t	i;
 	int		copy;

 	current = line;
 	quote = "\0";
 	escaped = 0;
 	new = ft_calloc(ft_strlen(line) * 2 + 1, 1);
 	i = 0;
 	while (*current)
 	{
 		copy = 1;
 		if (*quote != '\'' && *current == '\\' && !escaped)
		{
 			copy = !ft_strchr(" \"$`", current[1]);
			escaped = 2;
		}
 		else if (escaped && *current == '\\')
 			copy = !*quote;
 		else if (!escaped && !*quote && ft_strchr("\"'", *current))
 		{
 			quote = current;
 			copy = 0;
			new[i++] = '\x1b';
 		}
 		else if (!escaped && *current == *quote)
 		{
 			quote = "\0";
 			copy = 0;
 		}
 		escaped = (*quote != '\'' && *current == '\\' && escaped != 1);
 		if (copy)
 		{
			if ((*quote == '"' && ft_indexof(DQ_ESCAPES "\\", *current) != -1)
			|| (*quote == '\'' && ft_indexof(SQ_ESCAPES, *current) != -1)
			|| (!*quote && *current == SPACE))
				new[i++] = '\\';
 			new[i] = *current;
 			i++;
 		}
 		++current;
 	}
	*end = new + i;
 	return (new);
 }


void
	expand_argv(char **argv, t_vector *new)
{
	char	**current;
	char	*expanded;
	char	*dequoted;
	char	**splitted;
	char	*end;

	current = argv;
	while (*current)
	{
		//printf("curr: [%s]\n", *current);
		expanded = perform_expansions(*current);
		//printf("exp: [%s]\n", expanded);
		dequoted = remove_quotes_a(expanded, &end);
		//printf("deq: [%s]\n", dequoted);
		splitted = tokenize(dequoted, end);
		vector_append(new, splitted, argv_len(splitted));
		free(dequoted);
		free(splitted);
		free(expanded);
		current++;
	}
}

void
	expand_redir(char ***redir_ptr)
{
	char	**new;

	new = expand_and_dequote_tokens(*redir_ptr);
	free_tokens(*redir_ptr);
	*redir_ptr = new;
}

void
	expand_command(t_command *command)
{
	t_vector	*argv_vector;
	char		**splitted;


	if (command->expanded)
		return ;
	command->expanded = 1;
	argv_vector = new_vector(20, sizeof(char **));
	free_tokens(command->redirections);
	splitted = split_quotes(command->cmd);
	command->redirections = extract_redirects(splitted);
	free_tokens(command->argv);
	command->argv = get_pure_tokens(splitted);
	free_tokens(splitted);
	expand_argv(command->argv, argv_vector);
	expand_redir(&(command->redirections));
	free_tokens(command->argv);
	command->argv = argv_vector->bytes;
	command->cmd = get_command_path(command->argv[0]);
	free(argv_vector);
	return ;
}
