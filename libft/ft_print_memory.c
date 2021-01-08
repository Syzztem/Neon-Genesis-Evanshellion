/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 09:15:06 by lothieve          #+#    #+#             */
/*   Updated: 2019/11/06 15:45:53 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void
	print_adress(unsigned long long addr)
{
	int		i;
	int		mod;
	char	out[16];

	i = 16;
	while (--i >= 0)
	{
		mod = addr % 16;
		addr = addr / 16;
		out[i] = (mod > 9 ? mod + 'a' - 10 : mod + '0');
	}
	write(1, out, 16);
}

static void
	print_as_hex(int *c)
{
	char	mod;
	char	out[2];
	int		i;
	int		n;

	i = 2;
	n = *c;
	if (n < 0)
		n += 256;
	while (--i >= 0)
	{
		mod = n % 16;
		n = n / 16;
		out[i] = (mod > 9 ? mod + 'a' - 10 : mod + '0');
	}
	write(1, out, 2);
}

static void
	print_printable(char *c)
{
	if (*c >= 32 && *c < 127)
		write(1, c, 1);
	else if (*c)
		write(1, ".", 1);
}

static void
	print_hex_content(void *addr, int size)
{
	int i;

	i = -1;
	while (++i < 16 && i < size)
	{
		print_as_hex((int*)addr);
		if (i % 2 == 1)
			write(1, " ", 1);
		addr++;
	}
	while (i < 16)
	{
		write(1, "  ", 2);
		if (i % 2 == 1)
			write(1, " ", 1);
		i++;
	}
}

void
	ft_print_memory(void *addr, unsigned int size)
{
	unsigned int i;
	unsigned int j;

	j = 0;
	while (j < size)
	{
		i = 0;
		print_adress((unsigned long long)addr);
		write(1, ": ", 2);
		print_hex_content(addr, size - j);
		while (i < 16 && i < size)
		{
			print_printable((char *)addr);
			addr++;
			j++;
			i++;
		}
		write(1, "\n", 1);
	}
}
