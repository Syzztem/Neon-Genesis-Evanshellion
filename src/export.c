/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:17:00 by lothieve          #+#    #+#             */
/*   Updated: 2021/02/01 16:22:47 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int
	split_env(char *assign)
{
	int i;

	i = 0;
	while (assign[i] && assign[i] != '=')
		i++;
	if (!assign[i])
		return (-1);
	assign[i] = '\0';
	return (i + 1);
}

static void
	export_setenv(char *assign)
{
	int	split_index;

	split_index = split_env(assign);
	if (split_index == -1)
		return ;
	ft_setenv(assign, assign + split_index);
}

void
	builtin_export(char **av, char **envp)
{
	if (av[1])
		export_setenv(av[1]);
}
