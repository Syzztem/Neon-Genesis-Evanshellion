/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 14:28:09 by smaccary          #+#    #+#             */
/*   Updated: 2021/04/30 21:20:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector
	*vector_resize(t_vector *vector, size_t new_size)
{
	char	*new;
	size_t	ncpy;

	new = vect_ft_calloc(new_size, vector->obj_size);
	if (vector->len > new_size)
	{
		ncpy = new_size;
		vector->available = 0;
		vector->len = ncpy;
		vector->size = new_size;
	}
	else
	{
		ncpy = vector->len;
		vector->available += new_size - vector->size;
		vector->size = new_size;
	}
	vect_ft_memcpy(new, vector->bytes, ncpy * vector->obj_size);
	free(vector->bytes);
	vector->bytes = new;
	return (vector);
}

t_vector
	*vector_append(t_vector *vector, void *add, size_t count)
{
	if (count > vector->available)
		vector_resize(vector, (vector->size + count) * 2);
	vect_ft_memcpy(vector->bytes + vector->len * vector->obj_size, add,
				count * vector->obj_size);
	vector->len += count;
	vector->available -= count;
	return (vector);
}

t_vector
	*new_vector(size_t count, size_t size)
{
	t_vector	*vector;

	vector = malloc(sizeof(t_vector));
	vector->bytes = vect_ft_calloc(count, size);
	vector->size = count;
	vector->available = count;
	vector->len = 0;
	vector->obj_size = size;
	return (vector);
}

void
	vector_iter(t_vector *vector, void (*func)())
{
	size_t	index;

	index = 0;
	while (index < vector->len)
	{
		func(vector_at(vector, index));
		index++;
	}
}

void
	vector_clear(t_vector *vector, void (*func)())
{
	if (!vector)
		return ;
	if (func)
		vector_iter(vector, (void *)func);
	free_vector(vector);
}
