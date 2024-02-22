/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:44:50 by thzeribi          #+#    #+#             */
/*   Updated: 2024/02/22 07:49:18 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
** @name is_mandelbrot(); [Static Function]
** @brief TODO
** @param t_tab *fractol
** @param double cr
** @param double ci
**/
static int
	is_mandelbrot(t_data *data, double cr, double ci)
{
	double	zr;
	double	zi;
	double	tmp;
	int		i;

	i = 0;
	zr = 0;
	zi = 0;
	while (i <= MAX_ITER + data->fractal.resolution_shift)
	{
		if ((zr * zr + zi * zi) > 4.0)
		{
			data->math.count = i;
			return (0);
		}
		tmp = 2 * zr * zi + ci;
		zr = zr * zr - zi * zi + cr;
		zi = tmp;
		i++;
	}
			data->math.count = i;
	return (1);
}

/**
** @name init_mandelbrot();
** @brief This function init the mandelbrot set variable.
** @param t_tab *fractol
**/
void
	init_mandelbrot(t_data *data)
{
	data->math.min_r = -2;
	data->min_r = -2;
	data->math.max_r = data->math.min_r * -1 \
		* data->win_width / data->win_height;
	data->math.min_i = -2;
	data->math.max_i = data->math.min_i * -1 \
		* data->win_height / data->win_width;
}


/**
 ** @name mandelbrot();
 ** @brief Call by draw_fractol() function, this function draw the
 ** mandelbrot set.
 **
 ** @param t_data *data
 ** @return TRUE [1]
 **/
int
	mandelbrot(t_data *data)
{
	int		x;
	int		y;
	double	pr;
	double	pi;

	y = -1;
	while (++y < data->win_height)
	{
		pi = data->math.max_i + ((double)y \
			* (data->math.min_i - data->math.max_i) \
			/ data->win_height);
		x = -1;
		while (++x < data->win_width)
		{
			pr = data->math.min_r + ((double)x \
				* (data->math.max_r - data->math.min_r) \
				/ data->win_width);
			if (is_mandelbrot(data, pr, pi) == 0)
				my_mlx_pixel_put(&data->image, x, y, make_color(data));
			else
				my_mlx_pixel_put(&data->image, x, y, create_trgb(0, 0, 0, 0));
		}
	}
	return (TRUE);
}
