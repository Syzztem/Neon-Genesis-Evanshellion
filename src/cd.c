/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 14:06:59 by lothieve          #+#    #+#             */
/*   Updated: 2021/02/03 11:25:08 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

void	builtin_cd(char **av, char **envp)
{
	char	dir[PATH_MAX];

	(void)envp;
	if (av[1] && chdir(av[1]) == -1)
		return (handle_error("minishell: cd", av[1]));
	else if (!av[1] && chdir(ft_getenv("HOME")) == -1)
		return (handle_error("minishell: cd", ft_getenv("HOME")));
	getcwd(dir, PATH_MAX);
	ft_setenv("PWD", dir);
}
