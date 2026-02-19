/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phoenix_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:14:16 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/19 11:44:10 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double
	phoenix_smooth(int iter, double *sq, t_data *data)
{
	if (iter == data->fractal.max_iterations)
		return ((double)iter);
	return (iter + 1
		- fast_log2(fast_log2(sq[0] + sq[1]) * 0.5) * data->math.log_2);
}

static void
	phoenix_step(double *z, double *prev, double *sq, t_data *data)
{
	double	tmp[2];

	tmp[0] = z[0];
	tmp[1] = z[1];
	z[1] = 2.0 * z[0] * z[1] + data->fractal.phoenix_p * prev[1];
	z[0] = sq[0] - sq[1] + data->fractal.julia_shiftx
		+ data->fractal.phoenix_p * prev[0];
	prev[0] = tmp[0];
	prev[1] = tmp[1];
	sq[0] = z[0] * z[0];
	sq[1] = z[1] * z[1];
}

static double
	phoenix_loop(t_data *data, double cr, double ci)
{
	double	z[2];
	double	prev[2];
	double	sq[2];
	int		i;

	z[0] = cr;
	z[1] = ci;
	prev[0] = 0.0;
	prev[1] = 0.0;
	sq[0] = z[0] * z[0];
	sq[1] = z[1] * z[1];
	i = 0;
	while (sq[0] + sq[1] <= 4.0 && i < data->fractal.max_iterations)
	{
		phoenix_step(z, prev, sq, data);
		i++;
	}
	return (phoenix_smooth(i, sq, data));
}

void
	init_phoenix(t_data *data)
{
	data->math.min_r = -2.0;
	data->math.max_r = 2.0;
	data->math.min_i = -2.0;
	data->math.max_i = 2.0 * (double)data->win_height / (double)data->win_width;
	data->fractal.color_shift = 3;
	data->fractal.resolution_shift = 0;
	data->fractal.max_iterations = MAX_ITER;
	data->fractal.julia_shiftx = 0.5667;
	data->fractal.phoenix_p = -0.5;
	data->math.log_2 = 1.0 / log(2.0);
	data->fractal.iterate = &phoenix_loop;
}
