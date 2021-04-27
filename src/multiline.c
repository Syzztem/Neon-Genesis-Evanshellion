/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 10:48:36 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/27 09:53:56 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define ML_PROMPT "> "

char
	*set_prompt(char *prompt)
{
	static char	*stored = NULL;

	if (prompt)
		stored = prompt;
	return (stored);
}

char
	*prompt(void)
{
	return (set_prompt(NULL));
}

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

int
	verify_line(char *line)
{
	char		*begin;
	char		*quote;
	int			escaped;

	begin = line;
	escaped = 0;
	quote = "\0";
	while (*line)
	{
		if (*quote != '\'' && *line == '\\' && !escaped)
		{
			escaped = 1;
			line++;
			continue ;
		}
		if (!*quote && ft_strchr("\"'", *line) && !escaped)
			quote = line;
		else if (!escaped && *quote == *line)
			return (1);
		if (!*quote && *line == '(' && !escaped)
		{
			if (!handle_parenthesis(&line))
				return (0);
			continue ;
		}
		if (!*quote && *line == ')' && !escaped)
			return (-1);
		++line;
		escaped = 0;
	}
	if (escaped || *quote)
		return (0);
	return (1);
}

int
	complete_line(char **line)
{
	char	*buf;
	char	*new;
	int		code;
	int		ret;

	code = verify_line(*line);
	while (!code || code == -1)
	{
		ret = prompt_shell(&buf);
		if (code == -1 || ret <= 0)
		{
			if (code == -1)
				ft_putendl_fd(
					"minishell: syntax error near unexpected token `)'", 2);
			else if (ret >= 0)
				ft_putendl_fd("minishell: unexpected EOF", 2);
			return (ret);
		}
		new = ft_strjoin(*line, "\n");
		free(*line);
		*line = new;
		new = ft_strjoin(*line, buf);
		free(*line);
		free(buf);
		*line = new;
		code = verify_line(*line);
	}
	return (1);
}
