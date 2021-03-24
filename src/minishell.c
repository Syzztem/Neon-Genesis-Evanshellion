/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:00:48 by lothieve          #+#    #+#             */
/*   Updated: 2021/03/24 16:11:07 by smaccary         ###   ########.fr       */
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

int	is_shell_interactive(void)
{
	return (ft_isatty(0) && ft_isatty(1) && ft_isatty(2));
}

sig_t blank(int a)
{
	(void)a;
	if (is_shell_interactive())
		ft_putstr_fd("\n" PROMPT, 2);
	else
		exit(130);
	return (NULL);
}

#ifdef BONUS

static int
	prompt_shell(char **line)
{
	int		ret;
	t_term	term;
	t_term	backup;

	ft_putstr_fd(PROMPT, 2);
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
	if (is_shell_interactive())
		ft_putstr_fd(PROMPT, 2);
	return (get_next_line(0, line));
}

#endif

int is_computer_on(void)
{
	return (1);
}

static int
	minishell(void)
{
	char		*line;
	char		**tokens;
	extern char	**environ;

	if (!is_computer_on())
	{
		ft_putstr_fd("Computer is off, please turn it on.\n", 2);
		exit (1);
	}

	signal(SIGINT, (void *)blank);
	while (prompt_shell(&line))
	{
		if (!line)
		{
			perror("minishell: ");
			exit (errno);
		}
		if (!*line)
		{
			free(line);
			continue ;
		}
		tokens = tokenize(line);
		exec_command_line(tokens);
		free_tokens(tokens);
		free(line);

	}
	return (g_exit_status);
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
	print_exit();
	return (g_exit_status);
}

#endif
