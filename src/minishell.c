/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:00:48 by lothieve          #+#    #+#             */
/*   Updated: 2021/03/20 20:02:28 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include <limits.h>

int ft_isatty(int fd)
{
	struct termios	term;
	
  	return (tcgetattr(fd, &term) == 0);
}

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

	signal(SIGINT, (void *)blank);
	while (prompt_shell(&line))
	{
		if (!*line)
		{
			free(line);
			continue ;
		}
		tokens = tokenize(line);
		//exec_abstract_pipeline(tokens);
		exec_command_line(tokens);
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
