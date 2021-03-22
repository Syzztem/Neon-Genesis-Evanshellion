/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:43:19 by smaccary          #+#    #+#             */
/*   Updated: 2021/03/22 13:53:02 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void
	close_cmd(t_command *cmd)
{
	close_checked(cmd->fd_input);
	close_checked(cmd->fd_output);
}

void
    close_all_cmds(t_list *commands, t_command *avoid)
{
	t_list	*current;

	current = commands;
	while (current)
	{
		if (avoid != current->content)
			close_cmd(current->content);
		current = current->next;
	}
}
