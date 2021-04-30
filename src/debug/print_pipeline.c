/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 15:16:41 by smaccary          #+#    #+#             */
/*   Updated: 2021/04/30 15:17:14 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

void
	print_command(t_command *command)
{
	if (!DEBUG)
		return ;
	printf("%p:\n", command);
	if (command)
	{
		printf("  - %-15s", "cmd:");
		pesc(command->cmd, 1);
		ft_putstr_fd("\n", 1);
		printf("  - %-15s", "argv:");
		print_argv(command->argv);
		printf("  - %-15s", "tokens:");
		print_argv(command->tokens);
		printf("  - %-15s", "redirections:");
		print_argv(command->redirections);
		printf("  - %-15s", "sep:");
		pesc(command->sep, 1);
		write(1, "\n", 1);
		printf("  - %-15s%d\n  - %-15s%d\n", "input:", command->fd_input,
				"output:", command->fd_output);
		printf("  - %-15s%d\n\n", "pid:", command->pid);
	}
}

void
	print_pipeline(t_pipeline lst)
{
	if (!DEBUG)
		return ;
	ft_lstiter(lst, (void *)print_command);
}
