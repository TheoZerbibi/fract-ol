/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:05:36 by thzeribi          #+#    #+#             */
/*   Updated: 2024/02/22 07:21:00 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void
	change_color_shift(t_data *data)
{
	if (data->fractal.color_shift == 5)
		data->fractal.color_shift = 1;
	else
		data->fractal.color_shift++;
}

static int
	get_red(int color_value)
{
	if (color_value >= 0 && color_value <= 255)
		return (255);
	else if (color_value > 255 && color_value <= 510)
		return (255 - (color_value - 255));
	else if (color_value > 510 && color_value <= 1020)
		return (0);
	else if (color_value > 1020 && color_value <= 1275)
		return (color_value - 1020);
	else
		return (255);
}

static int
	get_green(int color_value)
{
	if (color_value >= 0 && color_value <= 255)
		return (color_value);
	else if (color_value > 255 && color_value <= 765)
		return (255);
	else if (color_value > 765 && color_value <= 1020)
		return (255 - (color_value - 765));
	else if (color_value > 1020 && color_value <= 1275)
		return (0);
	else
		return (255);
}

static int
	get_blue(int color_value)
{
	if (color_value >= 0 && color_value <= 510)
		return (0);
	if (color_value > 510 && color_value <= 765)
		return (color_value - 510);
	else
		return (255);
}

static void
	get_shift_offsets(t_data *data, int *r_off, int *g_off, int *b_off)
{
	*r_off = 0;
	*g_off = 0;
	*b_off = 0;

	if (data->fractal.color_shift == 1)
	{
		*r_off += 150;
		*b_off += 10;
	}
	else if (data->fractal.color_shift == 2)
	{
		*r_off += 70;
		*b_off += 70;
	}
	else if (data->fractal.color_shift == 3)
	{
		*g_off += 50;
	}
	else if (data->fractal.color_shift == 4)
	{
		*r_off += 64;
		*g_off += 64;
		*b_off += 64;
	}
	else
	{
		*r_off += 105;
		*g_off += 77;
		*b_off += 247;
	}
}

static int
	clamp_color(int c)
{
	if (c < 0)
		c = 0;
	else if (c > 255)
		c = 255;
	return (c);
}

int
	make_color(t_data *data, int iteration)
{
	int color_value;
	int r, g, b;
	int r_off, g_off, b_off;

	color_value = iteration * 15;
	r = get_red(color_value);
	g = get_green(color_value);
	b = get_blue(color_value);

	get_shift_offsets(data, &r_off, &g_off, &b_off);

	r = clamp_color(r + r_off);
	g = clamp_color(g + g_off);
	b = clamp_color(b + b_off);

	return create_trgb(0, r, g, b);
}