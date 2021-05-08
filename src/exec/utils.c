/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:21:31 by smaccary          #+#    #+#             */
/*   Updated: 2021/05/09 00:59:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "exec.h"

void
	pescaped_token(char *token, int fd)
{
	if (!token)
	{
		ft_putstr_fd("(null)", fd);
		return ;
	}
	while (*token)
	{
		if (*token != ESCAPE_CHAR)
			ft_putchar_fd(*token, fd);
		token++;
	}
}

void
	psyntax_error(char *token)
{
	ft_putstr_fd(SHELL_NAME ": syntax error near unexpected token `", 2);
	if (token)
		pescaped_token(token, 2);
	else
		ft_putstr_fd("(null)", 2);
	ft_putstr_fd("'\n", 2);
}

void
	pcmd_not_found(t_command *cmd)
{
	ft_putstr_fd(SHELL_NAME ": ", 2);
	if (ft_strchr(cmd->cmd, '/'))
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	else
		ft_putstr_fd("command not found: ", 2);
	pescaped_token(cmd->argv[0], 2);
	ft_putstr_fd("\n", 2);
}

void
	p_builtin_error(char *name, char *arg, char *error_msg)
{
	ft_putstr_fd(SHELL_NAME ": ", 2);
	pescaped_token(name, 2);
	ft_putstr_fd(": ", 2);
	if (arg)
	{
		pescaped_token(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd("\n", 2);
}
