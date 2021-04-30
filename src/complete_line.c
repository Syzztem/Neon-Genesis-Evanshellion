/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 20:34:16 by user42            #+#    #+#             */
/*   Updated: 2021/04/30 14:35:56 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	terminate_line(char **line, char *tmp)
{
	free(tmp);
	*line = NULL;
	return (1);
}

char
	*strjoin_newline_free(char *s1, char *s2)
{
	char	*new;

	new = strjoin_newline(s1, s2);
	free(s1);
	free(s2);
	return (new);
}

int
	complete_line(char **line, int ret)
{
	char	*tmp;

	set_prompt(ML_PROMPT);
	while (ret && (!*line || !verify_line(*line)))
	{
		tmp = NULL;
		ft_putstr_fd(prompt(), 2);
		if (*line)
			tmp = *line;
		ret = get_term_line(line);
		if (!ret)
			return (terminate_line(line, tmp));
		if (!ft_strcmp(prompt(), PROMPT))
		{
			free(tmp);
			break ;
		}
		if (*line && tmp && *line != tmp)
			*line = strjoin_newline_free(tmp, *line);
		else if (!*line)
			*line = tmp;
	}
	return (ret);
}
