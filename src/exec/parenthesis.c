/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 18:24:02 by smaccary          #+#    #+#             */
/*   Updated: 2021/05/08 18:24:19 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "tokenizer.h"
#include "vector.h"

int
	exec_parenthesis(t_command *cmd)
{
	extern char	**environ;

	if (redirect_command(cmd) < 0)
		return (-1);
	return (builtin_parenthesis(cmd->argv, environ));
}

int
	is_cmd_parenthesis(t_command *cmd)
{
	return (!ft_strcmp(PARENTHESIS_OPEN, cmd->cmd));
}
