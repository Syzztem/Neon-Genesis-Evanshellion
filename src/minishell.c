/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:00:48 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/31 14:36:42 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# ifdef BONUS

static int
	prompt_shell(char **line)
{
	ft_putstr_fd("EVA-04$ ", 0);
	return (get_term_line(line));
	return (0);
}

#else

static int
	prompt_shell(char **line)
{
	ft_putstr_fd("EVA-04$ ", 0);
	return (get_next_line(0, line));
	return (0);
}

#endif

int	print_tokenized(char *line)
{
	char	**tokens;
	int		i;

	if (!(tokens = tokenize(line)))
		return (EXIT_FAILURE);
	i = 0;
	while (tokens[i])
	{
		printf("\ntokens[%d]: %s | len: %zu\n", i, tokens[i], ft_strlen(tokens[i]));
		free(tokens[i]);
		i++;
	}
	free(tokens);
	return (EXIT_SUCCESS);
}

int		main(void)
{
	char	*line;

	while (prompt_shell(&line))
	{
		print_tokenized(line);
		free(line);
	}
	return (EXIT_SUCCESS);
}

/*
int		main(void)
{
	char	*line;

	while (prompt_shell(&line))
	{
		printf("\nLINE: [%s]\n", line);
		print_tokenized(line);
		free(line);
	}
	return (EXIT_SUCCESS);
}
*/
