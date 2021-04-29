/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 20:30:06 by user42            #+#    #+#             */
/*   Updated: 2021/04/29 22:53:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	init_signals(void)
{
	signal(SIGINT, (void *)interrupt_blank);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void
	interrupt_line(t_line *line)
{
	if (interrupt_singleton(-1))
	{
		interrupt_singleton(0);
		free(line->line);
		init_line(line);
	}
}
