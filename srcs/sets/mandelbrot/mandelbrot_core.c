/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:44:50 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/19 12:06:54 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int
	check_main_shapes(double cr, double ci)
{
	double	i2;
	double	tr;
	double	q;

	i2 = ci * ci;
	tr = cr - 0.25;
	q = tr * tr + i2;
	if (q * (q + tr) <= 0.25 * i2)
		return (1);
	tr = cr + 1.0;
	if (tr * tr + i2 <= 0.0625)
		return (1);
	return (0);
}

static int
	check_period(double zr, double zi, double *old, int *period)
{
	if (zr == old[0] && zi == old[1])
		return (1);
	(*period)++;
	if (*period > 8)
	{
		old[0] = zr;
		old[1] = zi;
		*period = 0;
	}
	return (0);
}

static double
	mandelbrot_loop(t_data *data, double cr, double ci)
{
	data->math.z[0] = 0.0;
	data->math.z[1] = 0.0;
	data->math.sq[0] = 0.0;
	data->math.sq[1] = 0.0;
	data->math.old[0] = 0.0;
	data->math.old[1] = 0.0;
	data->math.state[0] = 0;
	data->math.state[1] = 0;
	while (data->math.sq[0] + data->math.sq[1] <= 4.0
		&& data->math.state[0] < data->fractal.max_iterations)
	{
		data->math.z[1] = 2.0 * data->math.z[0] * data->math.z[1] + ci;
		data->math.z[0] = data->math.sq[0] - data->math.sq[1] + cr;
		data->math.sq[0] = data->math.z[0] * data->math.z[0];
		data->math.sq[1] = data->math.z[1] * data->math.z[1];
		data->math.state[0]++;
		if (check_period(data->math.z[0], data->math.z[1],
				data->math.old, &data->math.state[1]))
			return ((double)data->fractal.max_iterations);
	}
	if (data->math.state[0] == data->fractal.max_iterations)
		return ((double)data->math.state[0]);
	return (data->math.state[0] + 1
		- fast_log2(fast_log2(data->math.sq[0] + data->math.sq[1]) * 0.5)
		* data->math.log_2);
}

double
	is_mandelbrot(t_data *data, double cr, double ci)
{
	if (check_main_shapes(cr, ci))
		return ((double)data->fractal.max_iterations);
	return (mandelbrot_loop(data, cr, ci));
}

void
	init_mandelbrot(t_data *data)
{
	data->math.min_r = -2.0;
	data->math.max_r = 2.0;
	data->math.min_i = -2.0;
	data->math.max_i = 2.0 * (double)data->win_height / (double)data->win_width;
	data->fractal.color_shift = 1;
	data->fractal.resolution_shift = 0;
	data->fractal.max_iterations = MAX_ITER;
	data->math.log_2 = 1.0 / log(2.0);
	data->fractal.iterate = &is_mandelbrot;
}
