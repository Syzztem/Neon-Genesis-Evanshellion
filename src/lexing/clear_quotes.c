/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 21:10:43 by user42            #+#    #+#             */
/*   Updated: 2021/04/29 21:10:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	clear_escaped_quotes(char *command)
{
	char	*line;

	line = command;
	while (*line)
	{
		if (line[0] == '\\' && line[1] && ft_strchr("\"'", line[1]))
			ft_memmove(line, line + 1, ft_strlen(line));
		++line;
	}
}
