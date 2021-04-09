/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:00:48 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/09 14:20:39 by lothieve         ###   ########.fr       */
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


int is_computer_on(void)
{
	return (1);
}

int
	minishell_non_interactive(void)
{
	char		*line;
	char		*dequoted;
//	char		**tokens;
	char		**commands;
	int			ret;

	if (!is_computer_on())
	{
		ft_putstr_fd("Computer is off, please turn it on.\n", 2);
		exit (1);
	}
	signal(SIGINT, (void *)blank);
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
		dequoted = remove_quotes(line);
		puts(dequoted);
		commands = split_line(dequoted);
		print_argv(commands);
		/*
		tokens = tokenize(line);
		exec_command_line(tokens);
		free_tokens(tokens);
		*/
		free_tokens(commands);
		free(dequoted);
		free(line);
	}
	free(line);
	return (g_exit_status);
}


int
	minishell(void)
{
	char		*line;
	char		*dequote;
	char		**commands;

	if (!is_computer_on())
	{
		ft_putstr_fd("Computer is off, please turn it on.\n", 2);
		exit (1);
	}
	signal(SIGINT, (void *)blank);
	while ((prompt_shell(&line)))
	{
		if (!complete_line(&line))
			continue ;
		dequote = remove_quotes(line);
		commands = split_line(dequote);
		print_argv(commands);

		//working single command tokenizer
		char *command = perform_expansions(*commands);
		puts(command);
		char **tokens = tokenize(command);
		free(command);
		puts("tokens");
		print_argv(tokens);

//		exec_line(commands);
		free_tokens(commands);
		free(dequote);
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
