/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alone.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 08:53:38 by root              #+#    #+#             */
/*   Updated: 2021/04/27 08:53:41 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		+ (size_t)line * !!(flag & 0b100)  + (size_t)"\0" * !!(flag & 0b1000));
		escaped = (*quote != '\'' && *line == '\\' && !escaped);
		if ((!(flag & 0b100) * !(flag & 0b1000)) * (!(flag & 0b10) || !*quote)
		* (!(flag & 0b1) || (*quote && line[1] != *quote)))
			new[i++] = *line;
		++line;
	}
	return (new);
}
