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
	static t_color	p2[10] = {
	{20, 0, 60}, {60, 10, 130}, {30, 60, 200}, {0, 150, 220},
	{20, 220, 160}, {100, 240, 80}, {220, 220, 40}, {255, 140, 30},
	{230, 50, 80}, {140, 20, 140}};

	*size = 10;
	return (p2);
}

static t_color
	*get_p3(int *size)
{
	static t_color	p3[12] = {
	{5, 0, 0}, {40, 2, 0}, {90, 10, 0}, {150, 25, 0},
	{200, 50, 5}, {235, 90, 10}, {255, 140, 15}, {255, 190, 40},
	{255, 220, 90}, {255, 240, 160}, {255, 250, 220}, {255, 255, 255}};

	*size = 12;
	return (p3);
}

/**
 * @brief    Map an escape-time iteration count to an RGB color.
 *
 * Selects the active palette, scales the iteration value using
 * sqrt for perceptual uniformity, and interpolates between adjacent
 * palette entries for smooth gradients.
 *
 * @param    data       Application state (provides active palette index).
 * @param    iteration  Smooth fractional iteration count.
 * @return   32-bit TRGB color value.
 * @note     Scaling: fmod(sqrt(iteration) * 2.5, palette_size).
 */
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
	scaled = fmod(sqrt(iteration) * 2.5, (double)size);
	idx = (int)scaled;
	if (idx >= size - 1)
		c = pal[size - 1];
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
	data->dirty = 1;
}
