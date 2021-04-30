/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:00:48 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/30 22:13:32 by user42           ###   ########.fr       */
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
	ret = complete_line(line, ret);
	tcsetattr(0, 0, &backup);
	singleton_line(NULL, 1);
	return (ret);
}

int
	is_computer_on(void)
{
	return (1);
}

int
	get_full_line(char **line)
{
	int		ret;
	char	*tmp;

	ret = get_next_line(0, line);
	while (ret && *line && !verify_line(*line))
	{
		ret = get_next_line(0, &tmp);
		if (ret < 0 || !tmp)
		{
			free(*line);
			*line = NULL;
			return (ret);
		}
		*line = strjoin_newline_free(*line, tmp);
	}
	if (!*line)
		return (-1);
	return (ret);
}

int
	minishell_non_interactive(void)
{
	char		*line;
	int			ret;

	if (!is_computer_on())
	{
		ft_putstr_fd("Computer is off, please turn it on.\n", 2);
		exit(1);
	}
	init_signals();
	line = NULL;
	while ((ret = get_full_line(&line)) || ft_strlen(line))
	{
		if (!line || ret < 0)
		{
			printf("minishell: %s", strerror(errno));
			exit(errno);
		}
		exec_line(line);
		free(line);
	}
	free(line);
	return (g_exit_status);
}

int
	minishell(void)
{
	char		*line;

	if (!is_computer_on())
	{
		ft_putstr_fd("Computer is off, please turn it on.\n", 2);
		exit(1);
	}
	init_signals();
	line = NULL;
	while ((prompt_shell(&line)))
	{
		if (line && *line)
			exec_line(line);
		free(line);
		line = NULL;
	}
	free(line);
	return (g_exit_status);
}
