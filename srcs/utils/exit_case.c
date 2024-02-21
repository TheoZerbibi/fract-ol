/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 06:45:25 by thzeribi          #+#    #+#             */
/*   Updated: 2024/02/21 10:09:41 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
** @name exit_init();
** @brief Call when initialisation failed.
**
** @param t_data *data
**/
void
	exit_init(t_data *data)
{
	printf("\e[1;31mError\nA problem occurred during initialisation !\e[0m\n");
	_end_mlx(data, 1);
}
