/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_palette.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:14:16 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/19 10:47:49 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int
	nebula_dark(double t)
{
	int	r;
	int	g;
	int	b;

	r = (int)(t * t * 20);
	g = (int)(t * t * 15);
	b = (int)(5 + t * 70);
	return (create_trgb(0, r, g, b));
}

static int
	nebula_glow(double t)
{
	int	r;
	int	g;
	int	b;

	r = (int)(20 + t * 60);
	g = (int)(15 + t * 55);
	b = (int)(75 + t * 100);
	return (create_trgb(0, r, g, b));
}

static int
	nebula_warm(double t)
{
	int	r;
	int	g;
	int	b;

	r = (int)(80 + t * 175);
	g = (int)(70 + t * 120);
	b = (int)(175 - t * 140);
	return (create_trgb(0, r, g, b));
}

static int
	nebula_core(double t)
{
	int	r;
	int	g;
	int	b;

	r = 255;
	g = (int)(190 + t * 65);
	b = (int)(35 + t * 220);
	return (create_trgb(0, r, g, b));
}

int
	make_space_color(double ratio)
{
	if (ratio <= 0.001)
		return (create_trgb(0, 2, 2, 8));
	if (ratio < 0.20)
		return (nebula_dark(ratio / 0.20));
	if (ratio < 0.45)
		return (nebula_glow((ratio - 0.20) / 0.25));
	if (ratio < 0.80)
		return (nebula_warm((ratio - 0.45) / 0.35));
	if (ratio > 1.0)
		return (create_trgb(0, 255, 255, 255));
	return (nebula_core((ratio - 0.80) / 0.20));
}
