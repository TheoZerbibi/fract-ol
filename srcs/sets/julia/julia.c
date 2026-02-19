/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:14:16 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/19 11:11:06 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void
	render_pixel(t_data *data, unsigned int *px, double cr, double ci)
{
	double	it;

	it = data->fractal.iterate(data, cr, ci);
	if (it >= data->fractal.max_iterations)
		*px = create_trgb(0, 0, 0, 0);
	else
		*px = make_color(data, it);
}

static void
	render_row(t_data *data, unsigned int *row, int y, double *step)
{
	double	ci;
	int		x;

	ci = data->math.max_i + y * step[1];
	x = 0;
	while (x < data->win_width)
	{
		render_pixel(data, &row[x], data->math.min_r + x * step[0], ci);
		x++;
	}
}

int
	julia(t_data *data)
{
	unsigned int	*pixel;
	double			step[2];
	int				y;

	pixel = (unsigned int *)data->image.addr;
	step[0] = (data->math.max_r - data->math.min_r) / (double)data->win_width;
	step[1] = (data->math.min_i - data->math.max_i) / (double)data->win_height;
	y = 0;
	while (y < data->win_height)
	{
		render_row(data, pixel + y * (data->image.size_line / 4), y, step);
		y++;
	}
	return (TRUE);
}
