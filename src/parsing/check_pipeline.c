/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 00:12:40 by user42            #+#    #+#             */
/*   Updated: 2021/05/10 23:34:28 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "minishell.h"

int
	check_redirections(char **redirections)
{
	char	**current;

	current = redirections;
	if (!current || !*current)
		return (0);
	while (current && *current)
	{
		if (is_redirect(*current))
		{
			if (!current[1] || (!ft_strcmp(current[1], " ") && !current[2]))
			{
				psyntax_error(*current);
				return (1);
			}
			if (is_redirect(current[1]))
			{
				psyntax_error(current[1]);
				return (2);
			}
		}
		current++;
	}
	return (0);
}

int
	check_command(t_command *cmd)
{
	if (!cmd || (!cmd->argv || !cmd->redirections || !cmd->argv[0]))
		return (3);
	if (!(cmd->argv[0][0]) && !(cmd->cmd[0]) && !(cmd->redirections[0]))
		return (4);
	if (check_redirections(cmd->redirections))
		return (1);
	if (!cmd->argv)
		return (2);
	return (0);
}

int
	check_pipeline(t_pipeline pipeline)
{
	t_list		*current;
	int			err;

	current = pipeline;
	while (current)
	{
		err = check_command(current->content);
		if (err)
		{
			ft_putendl_fd(PIPE_ERR_MSG, 2);
			return (err);
		}
		current = current->next;
	}
	return (0);
}
