/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_wildcard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 14:58:03 by lothieve          #+#    #+#             */
/*   Updated: 2021/01/11 14:57:33 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include <unistd.h>

void print_list(t_token *list)
{
	if (list)
	{
		print_list(list->next);
		puts(list->token);
	}
}

int main(int ac, char **av)
{
	(void)ac;
	t_token *list;


//	char	buff[255];
//	puts(getcwd(buff, 255));

	chdir("testfolder");
	list = expand_wildcard(av[1]);
	print_list(list);
}
