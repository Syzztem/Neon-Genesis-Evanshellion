/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 19:26:01 by user42            #+#    #+#             */
/*   Updated: 2021/04/30 22:23:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	ft_isatty(int fd)
{
	struct termios	term;

	return (tcgetattr(fd, &term) == 0);
}

int
	is_shell_interactive(void)
{
	return (ft_isatty(0) && ft_isatty(1) && ft_isatty(2));
}
