/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:44:50 by thzeribi          #+#    #+#             */
/*   Updated: 2025/01/05 16:23:24 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 ** @name is_burningship_smooth(); [Function]
 ** @brief Determine if a point is in the Burning Ship fractal.
 ** @param t_data *data
 ** @param double cr Real part of the complex number
 ** @param double ci Imaginary part of the complex number
 ** @return Number of iterations or -1 if the point is in the set
 **/
double inline
    is_burningship_smooth(t_data *data, double cr, double ci)
{
	double zr = 0.0;
	double zi = 0.0;
	double zr2 = 0.0;
	double zi2 = 0.0;
	int i = 0;
	int max_iter = data->fractal.max_iterations + data->fractal.resolution_shift;

	while (i < max_iter)
	{
		zr = fabs(zr);
		zi = fabs(zi);
		zr2 = zr * zr;
		zi2 = zi * zi;
		if (zr2 + zi2 > 4.0)
		{
			double log_zn = log(zr2 + zi2) / 2.0;
			double nu = log(log_zn / log(2)) / log(2);
			double smooth_iter = i + 1 - nu;
			return smooth_iter;
		}
		double temp = zr2 - zi2 + cr;
		zi = 2.0 * zr * zi + ci;
		zr = temp;
		i++;
	}
	return (double)max_iter;
}

/**
 ** @name init_burningship();
 ** @brief Initialize the Burning Ship fractal parameters.
 ** @param t_data *data
 **/
void init_burning_ship(t_data *data)
{
	data->math.min_r = -2.0;
	data->math.max_r = 1.0;
	data->math.min_i = -2.0;
	data->math.max_i = 2.0;
	data->fractal.color_shift = 3;
	data->fractal.max_iterations = MAX_ITER;
	data->fractal.resolution_shift = 0;
}

typedef struct s_complex
{
	double re;
	double im;
}   t_complex;

/**
 ** @name burning_ship();
 ** @brief Draw the Burning Ship fractal.
 ** @param t_data *data
 ** @return TRUE [1]
 **/
int burning_ship(t_data *data)
{
	int x, y;
	double pr, pi;
	double it;
	double step_r = (data->math.max_r - data->math.min_r) / (double)data->win_width;
	double step_i = (data->math.max_i - data->math.min_i) / (double)data->win_height;
	t_complex c;

	for (y = 0; y < data->win_height; y++)
	{
		pi = data->math.min_i + y * step_i;
		for (x = 0; x < data->win_width; x++)
		{
			pr = data->math.min_r + x * step_r;
			c.re = pr;
			c.im = pi;
			it = is_burningship_smooth(data, pr, pi);

			if (it < (double)data->fractal.max_iterations)
				my_mlx_pixel_put(&data->image, x, y, make_color(data, it));
			else
				my_mlx_pixel_put(&data->image, x, y, create_trgb(0, 0, 0, 0));
		}
	}
	return (1);
}
