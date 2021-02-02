/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:00:48 by lothieve          #+#    #+#             */
/*   Updated: 2021/02/01 17:07:21 by lothieve         ###   ########.fr       */
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

static int
	minishell(void)
{
	char	*line;
	char	**tokens;

	while (prompt_shell(&line))
	{
		if (!*line)
			continue ;
		tokens = tokenize(line);
		builtin_echo(tokens, NULL);
		free(line);
	}
	return (EXIT_SUCCESS);
}

#ifdef BONUS

int		main(void)
{
	tgetent(NULL, ft_getenv("TERM"));
	t_term term;
	t_term backup;
	tcgetattr(0, &term);
	tcgetattr(0, &backup);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, 0, &term);
	setbuf(stdout, NULL);
	cap("ks");
	minishell();
	tcsetattr(0, 0, &backup);
	system("leaks a.out | awk '/----/{y=2;next}y' | lolcat");
	builtin_exit(NULL, NULL);
}

#else

int main(void)
{
	minishell();
	system("leaks a.out | awk '/----/{y=2;next}y' | lolcat");
	builtin_exit(NULL, NULL);
}

#endif
