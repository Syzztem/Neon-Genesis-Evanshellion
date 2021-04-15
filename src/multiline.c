/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 10:48:36 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/15 14:23:30 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define ML_PROMPT "dquote>"

static int
	prompt_shell(char **line)
{
	int		ret;
	t_term	term;
	t_term	backup;

	ft_putstr_fd(ML_PROMPT, 2);
	tcgetattr(0, &term);
	tcgetattr(0, &backup);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, 0, &term);
	ret = get_term_line(line);
	tcsetattr(0, 0, &backup);
	return (ret);
}

static size_t
	handle_parenthesis(char **line)
{
	char		*ref;
	unsigned	level;

	ref = *line;
	level = 1;
	while (*++ref && level)
	{
		if (*ref == '(' && *(ref - 1) != '\\')
			++level;
		if (*ref == ')' && *(ref - 1) != '\\')
			--level;
	}
	if (level)
		return (0);
	return (1);
}

static int
	verify_line(char *line)
{
	char		*begin;

	begin = line;
	while (*line)
	{
		if (*line == '\'' && (line == begin || *(line - 1) != '\\'))
			while (*++line != '\'')
				if (!*line)
					return (0);
		if (*line == '\"' && (line == begin || *(line - 1) != '\\'))
			while (*++line != '\"' || *(line - 1) == '\\')
				if (!*line)
					return (0);
		if (*line == '(' && (line == begin || *(line - 1) != '\\')
				&& !handle_parenthesis(&line))
			return (0);
		++line;
	}
	if (line != begin && *(line - 1) == '\\')
		return (0);
	return (1);
}

int
	complete_line(char **line)
{
	char *buf;
	char *new;

	while (!verify_line(*line))
	{
		if (!prompt_shell(&buf))
		{
			free(*line);
			return (0);
		}
		new = ft_strjoin(*line, buf);
		free(*line);
		free(buf);
		*line = new;
	}
	return (1);
}
