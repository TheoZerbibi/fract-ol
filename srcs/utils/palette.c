/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:05:36 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/20 15:45:00 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_color
	*get_p1(int *size)
{
	static t_color	p1[16] = {
	{66, 30, 15}, {25, 7, 26}, {9, 1, 47}, {4, 4, 73},
	{0, 7, 100}, {12, 44, 138}, {24, 82, 177}, {57, 125, 209},
	{134, 181, 229}, {211, 236, 248}, {241, 233, 191}, {248, 201, 95},
	{255, 170, 0}, {204, 128, 0}, {153, 87, 0}, {106, 52, 3}};

	*size = 16;
	return (p1);
}

static t_color
	*get_p2(int *size)
{
	static t_color	p2[7] = {{148, 0, 211}, {75, 0, 130}, {0, 0, 255},
	{0, 255, 0}, {255, 255, 0}, {255, 127, 0}, {255, 0, 0}};

	*size = 7;
	return (p2);
}

static t_color
	*get_p3(int *size)
{
	static t_color	p3[37] = {
	{7, 7, 7}, {31, 7, 7}, {47, 15, 7}, {71, 15, 7},
	{87, 23, 7}, {103, 31, 7}, {119, 31, 7}, {143, 39, 7},
	{159, 47, 7}, {175, 63, 7}, {191, 71, 7}, {199, 71, 7},
	{223, 79, 7}, {223, 87, 7}, {223, 87, 7}, {215, 95, 7},
	{215, 95, 7}, {215, 103, 15}, {207, 111, 15}, {207, 119, 15},
	{207, 127, 15}, {207, 135, 23}, {199, 135, 23}, {199, 143, 23},
	{199, 151, 31}, {191, 159, 31}, {191, 159, 31}, {191, 167, 39},
	{191, 167, 39}, {191, 175, 47}, {183, 175, 47}, {183, 183, 47},
	{183, 183, 55}, {207, 207, 111}, {223, 223, 159}, {239, 239, 199},
	{255, 255, 255}};

	*size = 37;
	return (p3);
}

int
	make_color(t_data *data, double iteration)
{
	t_color	*pal;
	t_color	c;
	double	scaled;
	int		size;
	int		idx;

	idx = (data->fractal.color_shift - 1) % NUM_PALETTES;
	if (idx == 0)
		pal = get_p1(&size);
	else if (idx == 1)
		pal = get_p2(&size);
	else
		pal = get_p3(&size);
	scaled = (iteration / (double)data->fractal.max_iterations) * (size - 1);
	if (scaled > size - 1)
		scaled = size - 1;
	idx = (int)scaled;
	if (idx >= size - 1)
		c = interpolate(pal[idx + size - 2], pal[idx + 1], 1.0);
	else
		c = interpolate(pal[idx], pal[idx + 1], scaled - idx);
	return (create_trgb(0, clamp_color(c.r),
			clamp_color(c.g), clamp_color(c.b)));
}

void
	change_color_shift(t_data *data)
{
	data->fractal.color_shift++;
	if (data->fractal.color_shift > NUM_PALETTES)
		data->fractal.color_shift = 1;
}
