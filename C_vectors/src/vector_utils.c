/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 21:20:03 by user42            #+#    #+#             */
/*   Updated: 2021/04/30 21:20:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void
	free_vector(t_vector *vector)
{
	free(vector->bytes);
	free(vector);
}

void
	*vector_at(t_vector *vector, size_t index)
{
	return (vector->bytes + index * vector->obj_size);
}

void
	*vector_end(t_vector *vector)
{
	return (vector->bytes + vector->len * vector->obj_size);
}
