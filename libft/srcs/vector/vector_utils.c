/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 18:48:20 by thzeribi          #+#    #+#             */
/*   Updated: 2022/09/22 16:42:54 by thzeribi         ###   ########.fr       */
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
	return (vector->bytes + index * vector->elem_size);
}

void
	*vector_end(t_vector *vector)
{
	return (vector->bytes + vector->len * vector->elem_size);
}
