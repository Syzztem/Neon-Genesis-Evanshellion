/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_wildcard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 14:58:03 by lothieve          #+#    #+#             */
/*   Updated: 2021/04/30 21:34:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include <unistd.h>

#define BLACK	"\033[0;30m"
#define RED		"\033[0;31m"
#define GREEN	"\033[0;32m"
#define YELLOW	"\033[0;33m"
#define BLUE	"\033[0;34m"
#define PURPLE	"\033[0;35m"
#define CYAN	"\033[0;36m"
#define WHITE	"\033[0;37m"

void print_list(t_token *list)
{
	if (list)
	{
		print_list(list->next);
		ft_putendl_fd(list->token, 1);
		free(list->token);
		free(list);
	}
}



int main(int ac, char **av)
{
	(void)ac;
	t_token *list;

	chdir("testfolder");
	list = expand_wildcard(av[1]);
	if (list)
		print_list(list);
	system("leaks a.out | awk '/----/{y=2;next}y' | lolcat");
}
