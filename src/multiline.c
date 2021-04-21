/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 10:48:36 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/21 14:27:21 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define ML_PROMPT "> "

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
	*line = ref;
	if (level)
		return (0);
	return (1);
}



/*					/!\ GAS FACTORY ALERT /!\
**                            \
**                             *%
**    .                         (&&.
**                      %        %%%&
**                     &%,       %%%%%
**                   *%%%.       %%%%%%
**                 *#####       \######
**               *(######      ,####(#(
**              #(((((((((.  *((((((((\
**             (((((((\\\((\(((\(((((\
**             \\\\\\\\\\*\\\\\\\\\\*    \
**             .\\\*\\ ,\\\\\*\*\\\\  .*\.
**               *\****   .*,  ***** ****
**          *      ,****       ****,*****
**          .**,     *,**  *** .***,,,.,,
**           .,,,,.  ,,,,.  .,,  ,,,. ,,,
**             ,,,,,,,,,, .   ,,     .,,..   .@@@ ,@@@
**               ,...      ,....    ,,.      .@@@ ,@@@
**                   .,          ..          .&@@ ,@@@
**   . .                   *@,               .&&@.,@@@
**                        *@@@*              .@@@ ,@@@
**                        \@@@\ .            .@@@ ,@@@
**                      (@@@@@@@\            .@@@ ,@@@
**               ,\     (@@@@@@@@@@@@@@(     .@@@ ,@@@    .
**               %@,    (@@@@@@@\     .@@    .@@@ ,@@@
**               #@, .  (@@@@@@@\      @@    .@@@ ,@@@         .
**              %@@@&%##&@@@@@@@\..   .@@.  @@@@@@@@@@&           .
**              %@@@@@@@@@@@@@@@\  &&  @@  \@@@@@@@@@@@,            .
**              %@@@(   \@@@@@@@\  &@  @@  \@@@@@@@@@@@,
**           #@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@,
**           #@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@,
**           *@@@@@@@@@@@@@@@@@@@@@@@&@@@@@@@@@@@@@@@@&
**
**					/!\ GAS FACTORY ALERT /!\
*/

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
			while (*++line != '\"' || (*(line - 1) == '\\' && (line - begin < 2 || line[-2] != '\\')))
				if (!*line)
					return (0);
		if (*line == '(' && (line == begin || *(line - 1) != '\\')
				&& !handle_parenthesis(&line))
			return (0);
		if (*line == ')')
			return (-1);
		++line;
	}
	if (line != begin && *(line - 1) == '\\'
	&& (line - 2 < begin || line[-2] != '\\'))
		return (0);
	return (1);
}

int
	complete_line(char **line)
{
	char	*buf;
	char	*new;
	int		code;

	code = verify_line(*line);
	while (!code || code == -1)
	{
		if (code == -1 || !prompt_shell(&buf))
		{
			if (code == -1)
				ft_putendl_fd(
					"minishell: syntax error near unexpected token `)'", 2);
			else
				ft_putendl_fd("minishell: unexpected EOF", 2);

			return (0);
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
