/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:36:07 by thzeribi          #+#    #+#             */
/*   Updated: 2024/02/21 12:36:40 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void
	usage_background(t_data *data, int color)
{
	int i;
	int j;

	i = data->win_width - 270;
	while (i < data->win_width - 10)
	{
		j = 15;
		while (j < 285)
		{
			my_mlx_pixel_put(&(data->image), i, j, color);
			j++;
		}
		i++;
	}
}

int
	draw_usage(t_data *data, int col)
{
	void	*mlx;
	void	*win;
	int		x;
	int		y;

	y = 20;
	mlx = data->mlx.mlx;
	win = data->mlx.win;
	x = data->win_width - 250;
	mlx_string_put(mlx, win, x - 15, y + 10, col, "Usage");
	mlx_string_put(mlx, win, x, y + 35, col, "Disable usage   space");
	// mlx_string_put(mlx, win, x, y + 55, col, "Move            < ^ v >");
	// mlx_string_put(mlx, win, x, y + 80, col, "Move            q w a d");
	// mlx_string_put(mlx, win, x, y + 105, col, "Zoom            + -");
	// mlx_string_put(mlx, win, x, y + 130, col, "Scale up        page up");
	// mlx_string_put(mlx, win, x, y + 155, col, "Scale down      page down");
	// mlx_string_put(mlx, win, x, y + 180, col, "Angle           q e");
	return (0);
}



