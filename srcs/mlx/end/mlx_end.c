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
 * @brief    Clean up MiniLibX resources and exit.
 *
 * Safely destroys the window, image, and display connection in the
 * required order to prevent memory leaks or double-frees.
 *
 * @param    data   Application state.
 * @param    err    Exit code to return to the OS.
 * @return   Never returns (calls exit).
 */
int
	end_mlx(t_data *data, int err)
{
	if (data->mlx.mlx)
	{
		if (data->mlx.win)
			mlx_destroy_window(data->mlx.mlx, data->mlx.win);
		if (data->image.image)
			mlx_destroy_image(data->mlx.mlx, data->image.image);
		if (data->histogram)
			free(data->histogram);
		mlx_loop_end(data->mlx.mlx);
		mlx_destroy_display(data->mlx.mlx);
		free(data->mlx.mlx);
	}
	exit(err);
}
