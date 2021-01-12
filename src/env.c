/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:56:50 by user42            #+#    #+#             */
/*   Updated: 2021/01/12 16:01:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		builtin_env(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->env[i])
	{
		ft_putstr_fd(shell->env[i++], 1);
		ft_putstr_fd("\n", 1);
	}
	return (0);
}