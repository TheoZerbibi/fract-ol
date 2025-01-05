/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:44:50 by thzeribi          #+#    #+#             */
/*   Updated: 2025/01/05 17:38:34 by thzeribi         ###   ########.fr       */
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
double inline
	is_mandelbrot_smooth(t_data *data, double cr, double ci) {
	int i = 0;
	double zr = 0.0;
	double zi = 0.0;
	double zr_sq = 0.0;
	double zi_sq = 0.0;

	while (zr_sq + zi_sq <= 4.0 && i < data->fractal.max_iterations)
	{
		// Calcul correct de zr et zi
		double temp_zr = zr_sq - zi_sq + cr;
		double temp_zi = 2.0 * zr * zi + ci;
		zr = temp_zr;
		zi = temp_zi;
		zr_sq = zr * zr;
		zi_sq = zi * zi;
		i++;
	}

	if (i == data->fractal.max_iterations)
		return (i);
	else
		// Lissage pour des couleurs plus douces
		return (i + 1 - log(log(sqrt(zr_sq + zi_sq))) / log(2.0));
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
	int     x;
	int     y;
	double  step_r;
	double  step_i;
	double  it;

	step_r = (data->math.max_r - data->math.min_r) / (double)data->win_width;
	step_i = (data->math.max_i - data->math.min_i) / (double)data->win_height;
	y = -1;
	while (++y < data->win_height)
	{
		double pi = data->math.min_i + y * step_i;
		x = -1;
		while (++x < data->win_width)
		{
			double pr = data->math.min_r + x * step_r;
			it = is_mandelbrot_smooth(data, pr, pi);
			if (it >= data->fractal.max_iterations)
				my_mlx_pixel_put(&data->image, x, y, create_trgb(0, 0, 0, 0));
			else
				my_mlx_pixel_put(&data->image, x, y, make_color(data, it));
		}
	}
	return (TRUE);
}
