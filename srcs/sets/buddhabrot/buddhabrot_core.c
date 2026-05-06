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
	ft_memset(sq, 0, sizeof(sq));
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

	px = (int)((zr - data->math.min_r) / (data->math.max_r - data->math.min_r)
			* data->win_width);
	py = (int)((zi - data->math.min_i) / (data->math.max_i - data->math.min_i)
			* data->win_height);
	if (px >= 0 && px < data->win_width && py >= 0 && py < data->win_height)
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
	ft_memset(sq, 0, sizeof(sq));
	i = 0;
	while (sq[0] + sq[1] <= 4.0 && i < data->fractal.max_iterations)
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

	data->math.min_r = BUDDHA_MIN_R;
	data->math.max_r = BUDDHA_MAX_R;
	data->math.min_i = BUDDHA_MIN_I;
	data->math.max_i = BUDDHA_MAX_I;
	data->fractal.color_shift = 4;
	data->fractal.resolution_shift = 0;
	data->fractal.max_iterations = BUDDHA_ITER;
	data->fractal.iterate = NULL;
	total = data->win_width * data->win_height;
	data->histogram = (unsigned int *)malloc(sizeof(unsigned int) * total);
	if (!data->histogram)
		return ;
	data->hist_max = 0;
	ft_memset(data->histogram, 0, sizeof(unsigned int) * total);
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
		cr = BUDDHA_MIN_R + BUDDHA_RANGE_R
			* ((double)(ft_rand() % BUDDHA_RAND_RES) / BUDDHA_RAND_RES);
		ci = BUDDHA_MIN_I + BUDDHA_RANGE_I
			* ((double)(ft_rand() % BUDDHA_RAND_RES) / BUDDHA_RAND_RES);
		if (escapes(cr, ci, data->fractal.max_iterations))
			trace_orbit(data, cr, ci);
		i++;
	}
}
