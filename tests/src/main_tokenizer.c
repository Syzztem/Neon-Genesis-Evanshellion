/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:54:14 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/11 17:45:00 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void print_tab(char **tab)
{
	int i = 0;
	while (tab[i])
	{
		puts(tab[i]);
		free(tab[i]);
		i++;
	}
	free(tab);
}

void test(char *str)
{
	print_tab(tokenize(str));
}

int main(int ac, char **av)
{
	(void) ac;
	test(av[1]);
	system("leaks a.out | grep leaks");
}