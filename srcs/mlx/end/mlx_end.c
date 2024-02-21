/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_end.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 05:41:02 by thzeribi          #+#    #+#             */
/*   Updated: 2024/02/21 09:40:56 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
** @name _end_mlx()
** @brief this function is called at the very end of the program. His goal
** is to free all MiniLibX allocated memory and exit.
**
** @param t_data *data
** @param int err
**/
int
	_end_mlx(t_data *data, int err)
{
	if (data->mlx.mlx)
	{
		if (data->mlx.win)
			mlx_destroy_window(data->mlx.mlx, data->mlx.win);
		if (data->image.image)
			mlx_destroy_image(data->mlx.mlx, data->image.image);
		mlx_loop_end(data->mlx.mlx);
		mlx_destroy_display(data->mlx.mlx);
	}
	exit(err);
}
