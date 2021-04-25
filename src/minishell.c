/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:00:48 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/25 16:26:55 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "termcaps.h"
#include "exec.h"
#include <limits.h>
#include "global.h"
#include <signal.h>
#include <time.h>

int ft_isatty(int fd)
{
	struct termios	term;
	
  	return (tcgetattr(fd, &term) == 0);
}

int	is_shell_interactive(void)
{
	return (ft_isatty(0) && ft_isatty(1) && ft_isatty(2));
}

int
	interrupt_singleton(int value)
{
	static int	flag = 0;

	if (value >= 0)
		flag = value;
	return (flag);
}

sig_t
	interrupt_blank(int a)
{
	t_line	*line;

	(void)a;
	interrupt_singleton(1);
	if (is_shell_interactive())
	{
		line = singleton_line(NULL, 0);
		if (line)
			move_cursor(get_term_width(), get_last_column(line));
		singleton_line(NULL, 1);
		ft_putstr_fd("\n" PROMPT, 2);
	}
	else
		exit(130);
	return (NULL);
}

sig_t
	blank_fork(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	return (0);
}

static int
	prompt_shell(char **line)
{
	int		ret;
	t_term	term;
	t_term	backup;

	signal(SIGINT, (void *)interrupt_blank);
		signal(SIGINT, (void *)interrupt_blank);

	//signal(SIGTSTP, SIG_IGN);
	set_prompt(PROMPT);
	ft_putstr_fd(PROMPT, 2);
	tcgetattr(0, &term);
	tcgetattr(0, &backup);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, 0, &term);
	ret = get_term_line(line);
	tcsetattr(0, 0, &backup);
	singleton_line(NULL, 1);
	return (ret);
}


int is_computer_on(void)
{
	return (1);
}

int
	minishell_non_interactive(void)
{
	char		*line;
	char		**commands;
	int			ret;

	if (!is_computer_on())
	{
		ft_putstr_fd("Computer is off, please turn it on.\n", 2);
		exit (1);
	}
	signal(SIGINT, (void *)interrupt_blank);
	while ((ret = get_next_line(0, &line)) || ft_strlen(line))
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
		commands = split_line(line);

		exec_command_line(commands);
		free_tokens(commands);
		free(line);
	}
	free(line);
	return (g_exit_status);
}


int
	minishell(void)
{
	char		*line;
	char		**commands;

	if (!is_computer_on())
	{
		ft_putstr_fd("Computer is off, please turn it on.\n", 2);
		exit (1);
	}
	while ((prompt_shell(&line)))
	{
		if (!*line || !complete_line(&line))
		{
			free(line);
			continue ;
		}
		commands = split_line(line);
		if (DEBUG)
			print_argv(commands);
		//signal(SIGINT, SIG_IGN);
		signal(SIGINT, (void *)blank_fork);
		exec_command_line(commands);
		free_tokens(commands);
		free(line);
	}
	return (g_exit_status);
}

int
	main(void)
{
	copy_env();
	if (is_shell_interactive())
	{
		tgetent(NULL, ft_getenv("TERM"));
		setbuf(stdout, NULL);
		cap("ks");
		minishell();
		print_exit();
	}
	else
		minishell_non_interactive();
	return (g_exit_status);
}
