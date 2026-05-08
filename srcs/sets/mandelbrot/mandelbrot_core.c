/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:44:50 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/20 14:00:00 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @brief    Fast cardioid and period-2 bulb test.
 *
 * Analytically detects whether a point lies inside the main cardioid or
 * the period-2 bulb of the Mandelbrot set, avoiding expensive iteration.
 *
 * @param    cr   Real part of the test point.
 * @param    ci   Imaginary part of the test point.
 * @return   1 if the point is inside a known region, 0 otherwise.
 * @note   Cardioid: q(q + (cr-0.25)) <= 0.25*ci^2 where q = (cr-0.25)^2 + ci^2.
 *         Period-2 bulb: (cr+1)^2 + ci^2 <= 1/16.
 */
int
	check_main_shapes(double cr, double ci)
{
	double		i2;
	double		tr;
	double		q;

	i2 = ci * ci;
	tr = cr - 0.25;
	q = tr * tr + i2;
	if (q * (q + tr) <= 0.25 * i2)
		return (1);
	tr = cr + 1.0;
	if (tr * tr + i2 <= 0.0625)
		return (1);
	return (0);
}

/**
 * @brief    Mandelbrot escape-time iteration with smooth coloring.
 *
 * Iterates z_{n+1} = z_n^2 + c starting from z_0 = 0 until escape
 * (|z|^2 > 4) or max_iterations is reached. Returns a smooth iteration
 * count using the normalized iteration count algorithm.
 *
 * @param    data   Application state (provides max_iterations).
 * @param    cr     Real part of c (pixel coordinate).
 * @param    ci     Imaginary part of c (pixel coordinate).
 * @return   Smooth fractional iteration count, or max_iterations if bounded.
 * @note     Formula: iter + 1 - log2(log2(|z|^2) / 2).
 *           Uses period checking to detect orbital cycles early.
 */
static double
	mandelbrot_loop(t_data *data, double cr, double ci)
{
	double	zr;
	double	zi;
	double	sq[2];
	double	old[2];
	int		state[2];

	zr = 0.0;
	zi = 0.0;
	ft_memset(sq, 0, sizeof(sq));
	ft_memset(old, 0, sizeof(old));
	ft_memset(state, 0, sizeof(state));
	while (sq[0] + sq[1] <= 4.0 && state[0] < data->fractal.max_iterations)
	{
		zi = 2.0 * zr * zi + ci;
		zr = sq[0] - sq[1] + cr;
		sq[0] = zr * zr;
		sq[1] = zi * zi;
		state[0]++;
		if (check_period(zr, zi, old, &state[1]))
			return ((double)data->fractal.max_iterations);
	}
	if (state[0] == data->fractal.max_iterations)
		return ((double)state[0]);
	return (state[0] + 1
		- fast_log2(fast_log2(sq[0] + sq[1]) * 0.5));
}

/**
 * @brief    Public Mandelbrot iteration entry point.
 *
 * Combines the cardioid/bulb fast-path with the full iteration loop.
 *
 * @param    data   Application state.
 * @param    cr     Real part of c.
 * @param    ci     Imaginary part of c.
 * @return   Smooth iteration count (max_iterations if inside the set).
 */
double	is_mandelbrot(t_data *data, double cr, double ci)
{
	if (check_main_shapes(cr, ci))
		return ((double)data->fractal.max_iterations);
	return (mandelbrot_loop(data, cr, ci));
}

void
	init_mandelbrot(t_data *data)
{
	data->math.min_r = -2.0;
	data->math.max_r = 2.0;
	data->math.min_i = -2.0;
	data->math.max_i = 2.0 * (double)data->win_height / (double)data->win_width;
	data->fractal.color_shift = 1;
	data->fractal.resolution_shift = 0;
	data->fractal.max_iterations = MAX_ITER;
	data->fractal.iterate = &is_mandelbrot;
}
