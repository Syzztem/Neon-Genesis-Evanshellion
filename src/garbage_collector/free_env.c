/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 19:23:27 by user42            #+#    #+#             */
/*   Updated: 2021/04/29 19:23:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

void
	free_env(void)
{
	extern char	**environ;
	char		**current;

	if (!environ)
		return ;
	current = environ;
	while (*current)
	{
		free(*current);
		current++;
	}
	free(environ);
}
