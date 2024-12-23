/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:44:50 by thzeribi          #+#    #+#             */
/*   Updated: 2024/02/22 07:49:18 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 ** @name is_burningship(); [Function]
 ** @brief Determine if a point is in the Burning Ship fractal.
 ** @param t_data *data
 ** @param double cr Real part of the complex number
 ** @param double ci Imaginary part of the complex number
 ** @return Number of iterations or -1 if the point is in the set
 **/
int
is_burningship(t_data *data, double cr, double ci)
{
    double zr = 0.0;
    double zi = 0.0;
    double tmp;
    int i = 0;
    int max_iter = MAX_ITER + data->fractal.resolution_shift;

    while (i <= max_iter)
    {
        double zr_abs = fabs(zr);
        double zi_abs = fabs(zi);
        double zr2 = zr_abs * zr_abs;
        double zi2 = zi_abs * zi_abs;

        if (zr2 + zi2 > 4.0)
            return (i);

        tmp = zr2 - zi2 + cr;
        zi = 2.0 * zr_abs * zi_abs + ci;
        zr = tmp;
        i++;
    }
    return (-1);
}

/**
 ** @name init_burningship();
 ** @brief Initialize the Burning Ship fractal parameters.
 ** @param t_data *data
 **/
void
init_burning_ship(t_data *data)
{
    data->math.min_r = -2.0;
    data->math.max_r = 1.0;
    data->math.min_i = -2.0;
    data->math.max_i = 2.0;
}


/**
 ** @name burning_ship();
 ** @brief Draw the Burning Ship fractal.
 ** @param t_data *data
 ** @return TRUE [1]
 **/
int
burning_ship(t_data *data)
{
    int x;
    int y;
    double pr;
    double pi;
    int it;
    double step_r = (data->math.max_r - data->math.min_r) / (double)data->win_width;
    double step_i = (data->math.max_i - data->math.min_i) / (double)data->win_height;

    y = -1;
    while (++y < data->win_height)
    {
        pi = data->math.max_i - y * step_i;
        x = -1;
        while (++x < data->win_width)
        {
            pr = data->math.min_r + x * step_r;
            it = is_burningship(data, pr, pi);
            if (it != -1)
                my_mlx_pixel_put(&data->image, x, y, make_color(data, it));
            else
                my_mlx_pixel_put(&data->image, x, y, create_trgb(0, 0, 0, 0));
        }
    }
    return (TRUE);
}
