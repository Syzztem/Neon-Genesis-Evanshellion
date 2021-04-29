/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 00:12:40 by user42            #+#    #+#             */
/*   Updated: 2021/04/30 00:13:08 by user42           ###   ########.fr       */
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
	if (check_redirections(cmd->redirections))
		return (1);
	if (!cmd->argv)
		return (2);
	return (0);
}

int
	check_pipeline(t_pipeline pipeline)
{
	t_list	*current;
	int		err;

	current = pipeline;
	while (current)
	{
		err = check_command(current->content);
		if (err)
			return (err);
		current = current->next;
	}
	return (0);
}
