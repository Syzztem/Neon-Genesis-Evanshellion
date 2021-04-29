/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:17:00 by lothieve          #+#    #+#             */
/*   Updated: 2021/02/04 14:56:19 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	split_env(char *assign)
{
	int i;

	i = 0;
	while (assign[i] && assign[i] != '=')
	{
		if (!ft_isalnum(assign[i]) && assign[i] != '_')
			return (-1);
		i++;
	}
	if (!assign[i])
		return (i);
	assign[i] = '\0';
	return (i + 1);
}

static int
	export_setenv(char *assign)
{
	int	split_index;

	split_index = split_env(assign);
	if (split_index == -1)
	{
		handle_error("minishell: export: ", assign, "not a valid identifier");
		return (1);
	}
	ft_setenv(assign, assign + split_index);
	return (0);
}

static void
	swap_str(char **s1, char **s2)
{
	char *sw;

	sw = *s1;
	*s1 = *s2;
	*s2 = sw;
}

static void
	bubblesort_tab(char **table)
{
	int i;
	int j;

	i = -1;
	while (table[++i])
	{
		j = 0;
		while (table[++j])
			if (ft_strcmp(table[j - 1], table[j]) > 0)
				swap_str(&table[j - 1], &table[j]);
	}
}

int
	builtin_export(char **av, char **envp)
{
	if (av[1])
		return (export_setenv(av[1]));
	bubblesort_tab(envp);
	while (*envp)
	{
		ft_putstr_fd("export ", 1);
		ft_putendl_fd(*envp, 1);
		envp++;
	}
	return (0);
}
