/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:11:04 by lothieve          #+#    #+#             */
/*   Updated: 2021/02/03 11:03:44 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>
#include <string.h>

void	ft_perror(const char *str)
{
	ft_putstr_fd(str, 2);
	ft_putendl_fd(strerror(errno), 2);
}
