/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 05:37:57 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/19 10:23:25 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void
	move_vertical_reverse(t_data *data, char direction, double height)
{
	if (direction == 'U')
	{
		data->math.min_i -= 0.1 * height;
		data->math.max_i -= 0.1 * height;
	}
	if (direction == 'D')
	{
		data->math.min_i += 0.1 * height;
		data->math.max_i += 0.1 * height;
	}
}

static void
	move_vertical(t_data *data, char direction)
{
	double	height;

	height = data->math.max_i - data->math.min_i;
	if (data->set == BURNING_SHIP || data->set == BUDDHABROT)
		move_vertical_reverse(data, direction, height);
	else
	{
		if (direction == 'U')
		{
			data->math.min_i += 0.1 * height;
			data->math.max_i += 0.1 * height;
		}
		if (direction == 'D')
		{
			data->math.min_i -= 0.1 * height;
			data->math.max_i -= 0.1 * height;
		}
	}
}

static void
	move_horizontal(t_data *data, char direction)
{
	double	width;

	width = data->math.max_r - data->math.min_r;
	if (direction == 'R')
	{
		data->math.min_r += 0.1 * width;
		data->math.max_r += 0.1 * width;
	}
	if (direction == 'L')
	{
		data->math.min_r -= 0.1 * width;
		data->math.max_r -= 0.1 * width;
	}
}

static void
	move(t_data *data, char direction)
{
	if (direction == 'U' || direction == 'D')
		move_vertical(data, direction);
	else
		move_horizontal(data, direction);
}

int
	keypress(int keycode, t_data *data)
{
	if (keycode == K_ESC)
		_end_mlx(data, 0);
	if (keycode == K_SPACE)
		data->fractal.julia_locked = !data->fractal.julia_locked;
	if (keycode == K_CTRL)
		data->show_usage = !data->show_usage;
	if (keycode == K_SHIFT)
		change_color_shift(data);
	if (keycode == K_E)
		data->perf.show_debug = !data->perf.show_debug;
	if (keycode == K_W || keycode == K_UP)
		move(data, 'U');
	if (keycode == K_S || keycode == K_DOWN)
		move(data, 'D');
	if (keycode == K_A || keycode == K_LEFT)
		move(data, 'L');
	if (keycode == K_D || keycode == K_RIGHT)
		move(data, 'R');
	if (keycode == K_W || keycode == K_UP || keycode == K_S
		|| keycode == K_DOWN || keycode == K_A || keycode == K_LEFT
		|| keycode == K_D || keycode == K_RIGHT)
		update_adaptive_iter(data);
	return (keycode);
}
