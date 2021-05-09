/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 20:11:05 by user42            #+#    #+#             */
/*   Updated: 2021/05/09 04:04:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** "Still reachables" on termcaps is a normal behaviour.
** See : https://invisible-island.net/ncurses/ncurses.faq.html#config_leaks
*/

int
	main(void)
{
	copy_env();
	if (is_shell_interactive())
	{
		tgetent(NULL, ft_getenv("TERM"));
		cap("ks");
		minishell();
		print_exit();
	}
	else
		minishell_non_interactive();
	free_env();
	return (g_exit_status);
}
