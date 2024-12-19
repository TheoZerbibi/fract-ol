/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:44:50 by thzeribi          #+#    #+#             */
/*   Updated: 2024/02/22 07:49:18 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
** @name is_mandelbrot(); [Static Function]
** @brief TODO
** @param t_tab *fractol
** @param double cr
** @param double ci
**/
int
	is_mandelbrot(t_data *data, double cr, double ci)
{
    double zr = 0;
    double zi = 0;
    double tmp;
    int i = 0;
    int max_iter = MAX_ITER + data->fractal.resolution_shift;

    while (i <= max_iter)
    {
        double zr2 = zr * zr;
        double zi2 = zi * zi;
        if (zr2 + zi2 > 4.0)
            return i;
        tmp = 2 * zr * zi + ci;
        zr = zr2 - zi2 + cr;
        zi = tmp;
        i++;
    }
    return -1;
}

/**
** @name init_mandelbrot();
** @brief This function init the mandelbrot set variable.
** @param t_tab *fractol
**/
void
	init_mandelbrot(t_data *data)
{
	data->math.min_r = -2;
	data->min_r = -2;
	data->math.max_r = data->math.min_r * -1 \
		* data->win_width / data->win_height;
	data->math.min_i = -2;
	data->math.max_i = data->math.min_i * -1 \
		* data->win_height / data->win_width;
}


/**
 ** @name mandelbrot();
 ** @brief Call by draw_fractol() function, this function draw the
 ** mandelbrot set.
 **
 ** @param t_data *data
 ** @return TRUE [1]
 **/
int
	mandelbrot(t_data *data)
{
	int		x;
	int		y;
	double	pr;
	double	pi;
	double step_r = (data->math.max_r - data->math.min_r) / data->win_width;
	double step_i = (data->math.min_i - data->math.max_i) / data->win_height;

	y = -1;
	while (++y < data->win_height)
	{
		pi = data->math.max_i + y * step_i;
		x = -1;
		while (++x < data->win_width)
		{
			pr = data->math.min_r + x * step_r;
			int it = is_mandelbrot(data, pr, pi);
            if (it == -1)
                my_mlx_pixel_put(&data->image, x, y, create_trgb(0, 0, 0, 0));
            else
                my_mlx_pixel_put(&data->image, x, y, make_color(data, it));
		}
	}
	return (TRUE);
}
