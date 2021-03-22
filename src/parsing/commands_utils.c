/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:14:38 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/22 14:16:27 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

size_t
	get_command_len(char **tokens)
{
	return (find_sep(tokens) - tokens);
}

int
	count_cmd(char **tokens)
{
	int		count;
	char	**current;

	current = tokens;
	count = 1;
	while (*current)
	{
		if (is_sep(*current))
			count++;
		current++;
	}
	return (count);
}
