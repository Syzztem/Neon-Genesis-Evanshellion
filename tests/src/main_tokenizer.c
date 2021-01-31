/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 14:54:14 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/27 16:44:55 by smaccary         ###   ########.fr       */
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
	//system("leaks a.out | awk '/----/{y=2;next}y' | lolcat");
}
