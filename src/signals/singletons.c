/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 19:21:28 by user42            #+#    #+#             */
/*   Updated: 2021/04/29 23:41:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	interrupt_singleton(int value)
{
	static int	flag = 0;

	if (value >= 0)
		flag = value;
	return (flag);
}

t_line
	*singleton_line(t_line *line, int mode)
{
	static t_line	*stored = NULL;

	if (mode)
		stored = line;
	return (stored);
}

char
	*set_prompt(char *prompt)
{
	static char	*stored = NULL;

	if (prompt)
		stored = prompt;
	return (stored);
}

char
	*prompt(void)
{
	return (set_prompt(NULL));
}
