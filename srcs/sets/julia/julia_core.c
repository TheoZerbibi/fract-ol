/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:14:16 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/19 11:42:13 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double
	julia_loop(t_data *data, double zr, double zi)
{
	double	sq[2];
	double	old[2];
	int		state[2];

	sq[0] = zr * zr;
	sq[1] = zi * zi;
	old[0] = 0.0;
	old[1] = 0.0;
	state[0] = 0;
	state[1] = 0;
	while (sq[0] + sq[1] <= 4.0 && state[0] < data->fractal.max_iterations)
	{
		zi = 2.0 * zr * zi + data->fractal.julia_shifty;
		zr = sq[0] - sq[1] + data->fractal.julia_shiftx;
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
	init_julia(t_data *data)
{
	data->math.min_r = -2.0;
	data->math.max_r = 2.0;
	data->math.min_i = -2.0;
	data->math.max_i = 2.0 * (double)data->win_height / (double)data->win_width;
	data->fractal.color_shift = 2;
	data->fractal.resolution_shift = 0;
	data->fractal.max_iterations = MAX_ITER;
	data->fractal.iterate = &julia_loop;
}
