/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:00:48 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/29 12:25:53 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	prompt_shell(char **line)
{
	//ft_putstr_fd("EVA-04$ ", 0);
	return (get_next_line(0, line));
	return (0);
}

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


/*
** MEMO:
** Entrer "abc abc abc" via le terminal cause le bug suivant:
** Le premier token vaudra "abc abc abc" au lieu de juste "abc"
** Les deux autres tokens auront la bonne valeur
** Ceci arrive dans tout les cas où le terminal est lu
** Même si la ligne lue n'est pas utilisée et remplacée par littérlement "abc abc abc" en dur, le bug se produira
** Cependant, si la ligne est codée en dur mais que stdin n'est pas lue, le bug disparaît
** Si on ne rentre rien dans stdin et que la ligne est codée en dur, le bug ne se prodit pas.
** Mais, si on rentre abc abc abc, une entrée qui ne sera pas utilisée, le bug se produit.
** En gros, sur deux strings identiques, si on écrit quelque chose dans le terminal et qu'on le lit, le comportement change,
** même dans le cas où on n'utilise pas l'entrée.
** Littéralement aucun sens.
*/

int		main(void)
{
	char	*line;
	char *gnl_line;
	int i;

	while (prompt_shell(&gnl_line))
	{
		free(gnl_line);
		line = "abc abc abc";
		i = -1;
		while (line[++i])
		{
			printf("%u ", line[i]);
		}
		printf("\n");
		print_tokenized(line);
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