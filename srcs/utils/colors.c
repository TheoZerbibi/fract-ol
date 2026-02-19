/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:05:36 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/19 11:00:01 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double
	lerp(double a, double b, double t)
{
	return (a + t * (b - a));
}

t_color
	interpolate(t_color c1, t_color c2, double t)
{
	t_color	result;

	result.r = (int)lerp(c1.r, c2.r, t);
	result.g = (int)lerp(c1.g, c2.g, t);
	result.b = (int)lerp(c1.b, c2.b, t);
	return (result);
}

int
	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int
	clamp_color(int c)
{
	if (c < 0)
		return (0);
	if (c > 255)
		return (255);
	return (c);
}

double
	smooth_iteration(int iteration, double zr, double zi)
{
	double	z_sq;

	if (iteration >= MAX_ITER)
		return ((double)iteration);
	z_sq = zr * zr + zi * zi;
	return (iteration + 1 - log(log(z_sq) * 0.5) / log(2));
}
