/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:00:48 by lothieve          #+#    #+#             */
/*   Updated: 2021/03/06 15:07:24 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include <limits.h>

sig_t blank(int a)
{
	(void)a;
	write(0, "\n" "EVA-04$ " , 9);
	return (NULL);
}

#ifdef BONUS

static int
	prompt_shell(char **line)
{
	int		ret;
	t_term	term;
	t_term	backup;

	ft_putstr_fd("EVA-04$ ", 0);
	tcgetattr(0, &term);
	tcgetattr(0, &backup);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, 0, &term);
	ret = get_term_line(line);
	tcsetattr(0, 0, &backup);
	return (ret);
}

#else

static int
	prompt_shell(char **line)
{
	ft_putstr_fd("EVA-04$ ", 0);
	return (get_next_line(0, line));
}

#endif

static int
	minishell(void)
{
	char		*line;
	char		**tokens;
	extern char	**environ;
	char		buf[PATH_MAX];

	signal(SIGINT, blank);
	while (prompt_shell(&line))
	{
		if (!*line)
		{
			free(line);
			continue ;
		}
	//	line = ft_strdup("pwd");
		tokens = tokenize(line);
	//	print_argv(tokens);
	//	printf("\n");
		exec_from_tokens(tokens);
		free_tab(tokens);
		free(line);
	}
	return (EXIT_SUCCESS);
}

#ifdef BONUS

int
	main(void)
{
	copy_env();
	tgetent(NULL, ft_getenv("TERM"));
	setbuf(stdout, NULL);
	cap("ks");
	minishell();
	builtin_exit(NULL, NULL);
}

#else

int
	main(void)
{	
	copy_env();
	minishell();
	//system("leaks minishell | awk '/----/{y=2;next}y' | /Users/lothieve/.brew/bin/lolcat");
	builtin_exit(NULL, NULL);
}

#endif
