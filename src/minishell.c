/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:00:48 by lothieve          #+#    #+#             */
/*   Updated: 2021/02/02 15:07:14 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

#ifdef BONUS

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
	char		*line;
	char		**tokens;
	extern char	**environ;
	char		buf[PATH_MAX];

	while (prompt_shell(&line))
	{
		if (!*line)
			continue ;
		tokens = tokenize(line);
		if (is_builtin(*tokens) != -1)
			exec_builtin(tokens, environ);
		else
			puts(find_exec(buf, *tokens));
		free_tab(tokens);
		free(line);
	}
	return (EXIT_SUCCESS);
}

#ifdef BONUS

int
	main(void)
{
	t_term term;
	t_term backup;

	copy_env();
	tgetent(NULL, ft_getenv("TERM"));
	tcgetattr(0, &term);
	tcgetattr(0, &backup);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, 0, &term);
	setbuf(stdout, NULL);
	cap("ks");
	minishell();
	tcsetattr(0, 0, &backup);
	system("leaks minishell | awk '/----/{y=2;next}y' | lolcat");
	builtin_exit(NULL, NULL);
}

#else

int
	main(void)
{
	copy_env();
	minishell();
	system("leaks minishell | awk '/----/{y=2;next}y' | lolcat");
	builtin_exit(NULL, NULL);
}

#endif
