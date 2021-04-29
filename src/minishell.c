/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:00:48 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/29 19:25:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "termcaps.h"
#include "exec.h"
#include <limits.h>
#include "global.h"
#include <signal.h>
#include <time.h>
#include <unistd.h>


static int
	prompt_shell(char **line)
{
	int		ret;
	char	*tmp;
	char	*new;
	t_term	term;
	t_term	backup;
	t_point	cursor;

	signal(SIGINT, (void *)interrupt_blank);
	signal(SIGQUIT, SIG_IGN);
	set_prompt(PROMPT);
	interrupt_singleton(0);
	tcgetattr(0, &term);
	tcgetattr(0, &backup);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, 0, &term);
	if (line && *line)
	{
		get_cursor(&cursor);
		if (cursor.x != 0)
			write(2, "\n", 1);
	}
	ft_putstr_fd(PROMPT, 2);
	ret = get_term_line(line);
	set_prompt("> ");
	while (ret && (!*line || !verify_line(*line)))
	{
		tmp = NULL;
		new = NULL;
		ft_putstr_fd(prompt(), 2);
		if (*line)
			tmp = *line;
		ret = get_term_line(line); 
		if (!ret)
		{
			free(tmp);
			*line = NULL;
			return (1);
		}
		if (!ft_strcmp(prompt(), PROMPT))
		{
			free(tmp);
			break ;
		}
		if (*line && tmp && *line != tmp)
		{
			new = strjoin_newline(tmp, *line);
			free(tmp);
			free(*line);
			*line = new;
		}
		else if (!*line)
			*line = tmp;
	}
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
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	while ((ret = get_next_line(0, &line)) || ft_strlen(line))
	{
		if (!line)
		{
			perror("minishell: ");
			exit (errno);
		}
		if (!*line || verify_line(line) <= 0)
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
	signal(SIGINT, (void *)interrupt_blank);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	while ((prompt_shell(&line)))
	{
		if (!line || !*line)
		{
			free(line);
			line = NULL;
			continue ;
		}
		commands = split_line(line);
		if (DEBUG)
			print_argv(commands);
		exec_command_line(commands);
		free_tokens(commands);
		free(line);
		line = NULL;
	}
	free(line);
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
	free_env();
	return (g_exit_status);
}
