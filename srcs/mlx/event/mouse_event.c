/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 05:39:15 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/20 14:00:00 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double
	get_zoom_factor(int keycode)
{
	if (keycode == 4)
		return (0.9);
	if (keycode == 5)
		return (1.1);
	return (0.0);
}

static int
	zoom_is_valid(t_data *data, double new_min_r, double new_max_r)
{
	double	range;
	double	step;

	range = new_max_r - new_min_r;
	if (range > INITIAL_ZOOM * 1.5)
		return (0);
	step = range / (double)data->win_width;
	if (step < 1e-13)
		return (0);
	return (1);
}

static void
	calc_cursor_pos(t_data *data, int x, int y, double *pos)
{
	double	w;
	double	h;

	w = data->math.max_r - data->math.min_r;
	h = data->math.max_i - data->math.min_i;
	pos[0] = data->math.min_r + ((double)x * w) / data->win_width;
	if (data->set == BURNING_SHIP)
		pos[1] = data->math.min_i + ((double)y * h) / data->win_height;
	else
		pos[1] = data->math.max_i - ((double)y * h) / data->win_height;
}

void
	update_adaptive_iter(t_data *data)
{
	double	zoom;
	int		iters;
	int		base;

	zoom = INITIAL_ZOOM / (data->math.max_r - data->math.min_r);
	if (zoom < 1.0)
		zoom = 1.0;
	base = MAX_ITER / 6;
	if (base < 50)
		base = 50;
	iters = base + (int)(log(zoom) / log(10.0) * (MAX_ITER - base));
	if (iters < base)
		iters = base;
	if (iters > MAX_ITER)
		iters = MAX_ITER;
	data->fractal.max_iterations = iters;
}

int
	mouse(int keycode, int x, int y, t_data *data)
{
	double	pos[2];
	double	zf;
	double	new_min_r;
	double	new_max_r;

	zf = get_zoom_factor(keycode);
	if (zf == 0.0)
		return (1);
	calc_cursor_pos(data, x, y, pos);
	new_min_r = pos[0] - (pos[0] - data->math.min_r) * zf;
	new_max_r = pos[0] + (data->math.max_r - pos[0]) * zf;
	if (!zoom_is_valid(data, new_min_r, new_max_r))
		return (1);
	data->math.min_r = new_min_r;
	data->math.max_r = new_max_r;
	data->math.min_i = pos[1] - (pos[1] - data->math.min_i) * zf;
	data->math.max_i = pos[1] + (data->math.max_i - pos[1]) * zf;
	update_adaptive_iter(data);
	return (1);
}
