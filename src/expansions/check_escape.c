/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_escape.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 20:10:27 by root              #+#    #+#             */
/*   Updated: 2021/05/08 15:28:41 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int
	check_escape(char *current, char *quote)
{
	return (
		(*quote == '"' && ft_indexof(DQ_ESCAPES "\\", *current) != -1)
		|| (*quote == '\'' && ft_indexof(SQ_ESCAPES, *current) != -1)
		|| (!*quote && current[0] == SPACE && current[-1] == '\\'));
}
