/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:44:50 by thzeribi          #+#    #+#             */
/*   Updated: 2025/01/05 07:08:19 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
** @name is_mandelbrot_smooth(); [Static Function]
** @brief TODO
** @param t_tab *fractol
** @param double cr
** @param double ci
**/
double
	is_mandelbrot_smooth(t_data *data, double cr, double ci) {
	double	zr;
	double	zi;
	double	tmp;
	int		i;
	int		max_iter;

	zr = 0;
	zi = 0;
	i = 0;
	max_iter = data->fractal.max_iterations + data->fractal.resolution_shift;
	while (i <= max_iter)
	{
		if ((zr * zr) + (zi * zi) > 4.0)
			return (smooth_iteration(i, zr, zi));
		tmp = 2 * zr * zi + ci;
		zr = (zr * zr) - (zi * zi) + cr;
		zi = tmp;
		i++;
	}
	return ((double)data->fractal.max_iterations);
}

/**
** @name init_mandelbrot();
** @brief This function init the mandelbrot set variable.
** @param t_tab *fractol
**/
void
	init_mandelbrot(t_data *data)
{
	data->math.min_r = -2.0;
	data->math.max_r = 2.0;
	data->math.min_i = -2.0;
	data->math.max_i = 2.0 * data->win_height / data->win_width;
	data->fractal.color_shift = 1;
	data->fractal.resolution_shift = 0;
	data->fractal.max_iterations = MAX_ITER;
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
	double	step_r;
	double	step_i;
	double	it;

	step_r = (data->math.max_r - data->math.min_r) / (double)data->win_width;
	step_i = (data->math.min_i - data->math.max_i) / (double)data->win_height;
	y = -1;
	while (++y < data->win_height)
	{
		x = -1;
		while (++x < data->win_width)
		{
			it = is_mandelbrot_smooth(data,
					data->math.min_r + x * step_r,
					data->math.max_i + y * step_i);
			if (it >= data->fractal.max_iterations)
				my_mlx_pixel_put(&data->image, x, y, create_trgb(0, 0, 0, 0));
			else
				my_mlx_pixel_put(&data->image, x, y, make_color(data, it));
		}
	}
	return (TRUE);
}
