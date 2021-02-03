/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errmgr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:58:37 by lothieve          #+#    #+#             */
/*   Updated: 2021/02/03 11:15:32 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <string.h>

void
	handle_error(char *command, char *arg)
{
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(strerror(errno), 2);
	errno = 0;
}
