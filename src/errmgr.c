/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errmgr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:58:37 by lothieve          #+#    #+#             */
/*   Updated: 2021/03/01 12:54:31 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <string.h>

int
	handle_error(char *command, char *arg, char *errmsg)
{
	int err;

	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (errmsg)
		ft_putendl_fd(errmsg, 2);
	else
		ft_putendl_fd(strerror(errno), 2);
	err = errno;
	errno = 0;
	return (err);
}
