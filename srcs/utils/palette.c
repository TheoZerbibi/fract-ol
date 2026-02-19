/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:05:36 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/19 10:53:06 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_color	g_palette1[] = {
{66, 30, 15}, {25, 7, 26}, {9, 1, 47}, {4, 4, 73},
{0, 7, 100}, {12, 44, 138}, {24, 82, 177}, {57, 125, 209},
{134, 181, 229}, {211, 236, 248}, {241, 233, 191}, {248, 201, 95},
{255, 170, 0}, {204, 128, 0}, {153, 87, 0}, {106, 52, 3}};

t_color	g_palette2[] = {{148, 0, 211}, {75, 0, 130}, {0, 0, 255}, {0, 255, 0},
{255, 255, 0}, {255, 127, 0}, {255, 0, 0}};

t_color	g_palette3[] = {
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

int		g_palette1_size = sizeof(g_palette1) / sizeof(t_color);
int		g_palette2_size = sizeof(g_palette2) / sizeof(t_color);
int		g_palette3_size = sizeof(g_palette3) / sizeof(t_color);

static void
	get_palette_info(t_data *data, t_color **pal, int *size)
{
	int	idx;

	idx = (data->fractal.color_shift - 1) % NUM_PALETTES;
	if (idx == 0)
	{
		*pal = g_palette1;
		*size = g_palette1_size;
	}
	else if (idx == 1)
	{
		*pal = g_palette2;
		*size = g_palette2_size;
	}
	else
	{
		*pal = g_palette3;
		*size = g_palette3_size;
	}
}

int
	make_color(t_data *data, double iteration)
{
	t_color	*pal;
	double	scaled;
	double	frac;
	int		size;
	int		idx;

	get_palette_info(data, &pal, &size);
	scaled = (iteration / MAX_ITER) * (size - 1);
	if (scaled > size - 1)
		scaled = size - 1;
	idx = (int)scaled;
	frac = scaled - idx;
	if (idx >= size - 1)
	{
		idx = size - 2;
		frac = 1.0;
	}
	return (
		create_trgb(0,
			clamp_color(interpolate(pal[idx], pal[idx + 1], frac).r),
			clamp_color(interpolate(pal[idx], pal[idx + 1], frac).g),
			clamp_color(interpolate(pal[idx], pal[idx + 1], frac).b)));
}

void
	change_color_shift(t_data *data)
{
	data->fractal.color_shift++;
	if (data->fractal.color_shift > NUM_PALETTES)
		data->fractal.color_shift = 1;
}
