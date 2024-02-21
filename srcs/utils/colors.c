/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:05:36 by thzeribi          #+#    #+#             */
/*   Updated: 2024/02/21 11:24:34 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


static void
	apply_shift(t_data *data)
{
	if (data->fractal.color_shift == 1)
	{
		data->color.r += 150;
		data->color.b += 10;
	}
	else if (data->fractal.color_shift == 2)
	{
		data->color.r += 70;
		data->color.b += 70;
	}
	else if (data->fractal.color_shift == 3)
		data->color.g += 75;
	else if (data->fractal.color_shift == 4)
		data->color.b += 140;
	else
	{
		data->color.r += 105;
		data->color.g += 77;
		data->color.b += 247;
	}
	return ;
}
static
	int	get_red(int color_value)
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

static
	int	get_green(int color_value)
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

int	make_color(t_data *data)
{
	int	color_value;

	color_value = data->fractal.math.count * 15;
	data->color.r = get_red(color_value);
	data->color.g = get_green(color_value);
	data->color.b = get_blue(color_value);
	apply_shift(data);
	return (create_trgb(0, data->color.r, data->color.g, \
			data->color.b));
}
