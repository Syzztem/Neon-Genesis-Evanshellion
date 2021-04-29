/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:24:50 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/29 21:22:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

/*
** char
** 	*remove_quotes(char *line)
** {
** 	char	*current;
** 	char	*quote;
** 	int		escaped;
** 	char	*new;
** 	size_t	i;
** 	int		copy;
**
** 	current = line;
** 	quote = "\0";
** 	escaped = 0;
** 	new = ft_calloc(ft_strlen(line) + 1, 1);
** 	i = 0;
** 	while (*current)
** 	{
** 		copy = 1;
** 		if (*quote != '\'' && *current == '\\' && !escaped)
** 			copy = *quote && !ft_strchr("\"$`", current[1]);
** 		else if (escaped && *current == '\\')
** 			copy = !*quote;
** 		else if (!escaped && !*quote && ft_strchr("\"'", *current))
** 		{
** 			quote = current;
** 			copy = 0;
** 		}
** 		else if (!escaped && *current == *quote)
** 		{
** 			quote = "\0";
** 			copy = 0;
** 		}
** 		escaped = (*quote != '\'' && *current == '\\' && !escaped);
** 		if (copy)
** 		{
** 			new[i] = *current;
** 			i++;
** 		}
** 		++current;
** 	}
** 	return (new);
** }
*/

/*
** remove quotes and backslashes from a string
*/

/*
**									ASSERT DOMINANCE
**                                         ....--.
**                                   ``....-/++++/-...
**                                   ``.://+++++-.....
**                                   :++++++++++:...--
**                                ``:++++++++++++-.../.
**                                `../+::::/+:++:++//+-
**                                   :+:/:.-:-//.+++++/`.
**                             `...-.-+///:---/+/+++++++++++++++++/.....
**                 `.....://+++o+++++++++++////+o++o++++/::::-----.
**                 ......----:::-----//:++o+//+o++++/++++:.
**                                   /:`/+++::+o+++:./+++++/-.
**                                   ::..-/++ooooo+/``-/++++/.-
**                                      ``.+oooo+oo+/-.`.-/++..
**                                      ``-ooooooooooos/.`-::
**                                      `/hysooyooooshdds-`.
**                                   ``.sddddddddhdddddddy/.
**                                   -ohdddddddddddddddddddh/
**                                   `:yhhddddddddddddddss+:
**                                      ``-+++syy+:::-::
**                                         ohhhhy.yhdhh/
**                                         `shhhy`/hhhh-
**                                         `:hhhh:.hhhh:
**                       ``.:://++oooo++/.``.hhhh-`yhhhs
**                 ...::/+oosssssssssssssys/.hhhh-`+hhhy
**              .::+ooooo++ossssssssssssssyh/shhh.`:hhh
**           ``/sso/----:/sssssssssssssssssys/hhh.`.yhh-
**           .oss+........osssssssssssysssshy-yhy.``shh.
**          .osss/.......-ssssssssssssssssyhhyyhy-..oyy.
**          -ossss:......+sssssssssssssssssys+/--...........
**          ``-::--......osssssss/++osssssssos:...`........
**									ASSERT DOMINANCE
*/

char
	*remove_quotes(char *line)
{
	char				*quote;
	int					escaped;
	char				*new;
	unsigned int		flag;
	size_t				i;

	quote = "\0";
	escaped = 0;
	new = ft_calloc(ft_strlen(line) + 1, 1);
	i = 0;
	while (*line)
	{
		flag = 0 | (*quote != '\'' && *line == '\\' && !escaped) | (escaped &&
		*line == '\\') << 1 | (!escaped && !*quote && ft_strchr("\"'", *line))
		<< 2 | (!escaped && *line == *quote) << 3;
		quote = (char *)((size_t)quote * (!(flag & 0b100) && !(flag & 0b1000))
		+ (size_t)line * !!(flag & 0b100) + (size_t)"\0" * !!(flag & 0b1000));
		escaped = (*quote != '\'' && *line == '\\' && !escaped);
		if ((!(flag & 0b100) * !(flag & 0b1000)) * (!(flag & 0b10) || !*quote)
		* (!(flag & 0b1) || (*quote && !ft_strchr("\"$`", line[1]))))
			new[i++] = *line;
		++line;
	}
	return (new);
}
