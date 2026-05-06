/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship_core.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:44:50 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/20 14:00:00 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	ship_loop(t_data *data, double cr, double ci)
{
	double	zr;
	double	zi;
	double	sq[2];
	double	old[2];
	int		state[2];

	zr = 0.0;
	zi = 0.0;
	sq[0] = 0.0;
	sq[1] = 0.0;
	old[0] = 0.0;
	old[1] = 0.0;
	state[0] = 0;
	state[1] = 0;
	while (sq[0] + sq[1] <= 4.0 && state[0] < data->fractal.max_iterations)
	{
		if (zr < 0.0)
			zr = -zr;
		if (zi < 0.0)
			zi = -zi;
		zi = 2.0 * zr * zi + ci;
		zr = sq[0] - sq[1] + cr;
		sq[0] = zr * zr;
		sq[1] = zi * zi;
		state[0]++;
		if (check_period(zr, zi, old, &state[1]))
			return ((double)data->fractal.max_iterations);
	}
	if (state[0] == data->fractal.max_iterations)
		return ((double)state[0]);
	return (state[0] + 1
		- fast_log2(fast_log2(sq[0] + sq[1]) * 0.5));
}

void
	init_burning_ship(t_data *data)
{
	data->math.min_r = -2.0;
	data->math.max_r = 1.0;
	data->math.min_i = -2.0;
	data->math.max_i = 2.0;
	data->fractal.color_shift = 3;
	data->fractal.max_iterations = MAX_ITER;
	data->fractal.resolution_shift = 0;
	data->fractal.iterate = &ship_loop;
}
