/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 10:48:36 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/29 23:42:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	prompt_shell(char **line)
{
	int		ret;
	t_term	term;
	t_term	backup;

	set_prompt(ML_PROMPT);
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

	if (!line || !*line)
		return (1);
	ref = *line + 1;
	level = 1;
	while (*ref && level)
	{
		if (*ref == '(' && *(ref - 1) != '\\')
			++level;
		if (*ref == ')' && *(ref - 1) != '\\')
			--level;
		ref++;
	}
	*line = ref;
	if (level)
		return (0);
	return (1);
}

static void
	set_quote(char **quote, char *line, int escaped)
{
	static char	*zero = "\0";

	if (!**quote && ft_strchr("\"'", *line) && !escaped)
		*quote = line;
	else if (!escaped && **quote == *line)
		*quote = zero;
}

int
	verify_line(char *line)
{
	char		*quote;
	int			escaped;

	escaped = 0;
	quote = "\0";
	while (*line)
	{
		if (*quote != '\'' && *line == '\\' && !escaped)
			escaped = 1;
		else
		{
			set_quote(&quote, line, escaped);
			if (!*quote && *line == '(' && !escaped)
			{
				if (!handle_parenthesis(&line))
					return (0);
				continue ;
			}
			if (!*quote && *line == ')' && !escaped)
				return (-1);
			escaped = 0;
		}
		++line;
	}
	return (!(escaped || *quote));
}
