/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 05:39:15 by thzeribi          #+#    #+#             */
/*   Updated: 2025/01/05 17:38:56 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int
	redraw_fractal(t_data *data)
{
    if (data->fractal.draw)
    {
        if (!data->fractal.draw(data))
            return (FALSE);
    }
    memcpy(data->image.addr, data->image.buffer, data->win_width * data->win_height * sizeof(unsigned int));
    mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->image.image, 0, 0);

    return (TRUE);
}

void
	clear_image(t_img *image)
{
	memset(image->addr, 0, image->size_line * image->height);
}

/**
 ** @name mouse();
 ** @brief Handle mouse events for zooming.
 ** @param int keycode
 ** @param int x X position of the mouse
 ** @param int y Y position of the mouse
 ** @param t_data *data
 ** @return 1
 **/
int
mouse(int keycode, int x, int y, t_data *data)
{
    double cx;
    double cy;
    double zoom_factor;

    // Calculer les coordonnées du centre du zoom
    cx = data->math.min_r + ((double)x * (data->math.max_r - data->math.min_r)) / data->win_width;
    if (data->set == BURNING_SHIP)
        cy = data->math.min_i + ((double)y * (data->math.max_i - data->math.min_i)) / data->win_height;
    else
        cy = data->math.max_i - ((double)y * (data->math.max_i - data->math.min_i)) / data->win_height;

    // Debugging
    printf("Zoom center: (%f, %f)\n", cx, cy);

    // Déterminer le facteur de zoom basé sur le keycode
    if (keycode == 4) // Zoom avant
        zoom_factor = 0.9;
    else if (keycode == 5) // Zoom arrière
        zoom_factor = 1.1;
    else
        return (1); // Ignorer les autres keycodes

    // Appliquer le zoom aux coordonnées
    data->math.min_r = cx - (cx - data->math.min_r) * zoom_factor;
    data->math.max_r = cx + (data->math.max_r - cx) * zoom_factor;
    data->math.min_i = cy - (cy - data->math.min_i) * zoom_factor;
    data->math.max_i = cy + (data->math.max_i - cy) * zoom_factor;

    // Debugging
    printf("New bounds after zoom:\n");
    printf("min_r: %f, max_r: %f\n", data->math.min_r, data->math.max_r);
    printf("min_i: %f, max_i: %f\n", data->math.min_i, data->math.max_i);

    // Ajuster dynamiquement max_iterations
    adjust_max_iterations(data);

    // Redessiner la fractale après le zoom
    redraw_fractal(data);

    return (1);
}

