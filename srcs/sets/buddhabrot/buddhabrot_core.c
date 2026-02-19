/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddhabrot_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:14:16 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/19 11:05:18 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int
	escapes(double cr, double ci, int max_iter)
{
	double	zr;
	double	zi;
	double	sq[2];
	int		i;

	zr = 0.0;
	zi = 0.0;
	sq[0] = 0.0;
	sq[1] = 0.0;
	i = 0;
	while (sq[0] + sq[1] <= 4.0 && i < max_iter)
	{
		zi = 2.0 * zr * zi + ci;
		zr = sq[0] - sq[1] + cr;
		sq[0] = zr * zr;
		sq[1] = zi * zi;
		i++;
	}
	return (i < max_iter);
}

static void
	record_hit(t_data *data, double zr, double zi)
{
	int	px;
	int	py;

	px = (int)((zr - data->math.min_r) / (data->math.max_r
				- data->math.min_r) * data->win_width);
	py = (int)((zi - data->math.min_i) / (data->math.max_i
				- data->math.min_i) * data->win_height);
	if (px >= 0 && px < data->win_width && py >= 0
		&& py < data->win_height)
		data->histogram[py * data->win_width + px]++;
}

static void
	trace_orbit(t_data *data, double cr, double ci)
{
	double	zr;
	double	zi;
	double	sq[2];
	int		i;

	zr = 0.0;
	zi = 0.0;
	sq[0] = 0.0;
	sq[1] = 0.0;
	i = 0;
	while (sq[0] + sq[1] <= 4.0
		&& i < data->fractal.max_iterations)
	{
		zi = 2.0 * zr * zi + ci;
		zr = sq[0] - sq[1] + cr;
		sq[0] = zr * zr;
		sq[1] = zi * zi;
		record_hit(data, zr, zi);
		i++;
	}
}

void
	init_buddhabrot(t_data *data)
{
	int	total;

	data->math.min_r = -2.0;
	data->math.max_r = 1.0;
	data->math.min_i = -1.5;
	data->math.max_i = 1.5;
	data->fractal.color_shift = 4;
	data->fractal.resolution_shift = 0;
	data->fractal.max_iterations = MAX_ITER;
	data->math.log_2 = 1.0 / log(2.0);
	data->fractal.iterate = NULL;
	total = data->win_width * data->win_height;
	data->histogram = (unsigned int *)malloc(sizeof(unsigned int) * total);
	if (!data->histogram)
		return ;
	data->hist_max = 0;
	while (--total >= 0)
		data->histogram[total] = 0;
}

void
	sample_buddhabrot(t_data *data, int num_samples)
{
	int		i;
	double	cr;
	double	ci;

	i = 0;
	while (i < num_samples)
	{
		cr = data->math.min_r + (data->math.max_r - data->math.min_r)
			* ((double)(rand() % 10000) / 10000.0);
		ci = data->math.min_i + (data->math.max_i - data->math.min_i)
			* ((double)(rand() % 10000) / 10000.0);
		if (escapes(cr, ci, data->fractal.max_iterations))
			trace_orbit(data, cr, ci);
		i++;
	}
}
