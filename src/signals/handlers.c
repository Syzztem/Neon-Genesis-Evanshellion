/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 19:21:45 by user42            #+#    #+#             */
/*   Updated: 2021/05/08 17:27:41 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	g_exit_status = 1;
	return (NULL);
}

sig_t
	blank_fork(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_exit_status = 130;
	return (0);
}
