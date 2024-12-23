/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 05:39:15 by thzeribi          #+#    #+#             */
/*   Updated: 2024/02/22 07:54:18 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int
	mouse(int keycode, int x, int y, t_data *data)
{
    double cx;
    double cy;
    double width;
    double height;
    double zoom_factor;

	cx = data->math.min_r + ((double)x * (data->math.max_r - data->math.min_r)) / data->win_width;
	cy = data->math.max_i + ((double)y * (data->math.min_i - data->math.max_i)) / data->win_height;
    width = data->math.max_r - data->math.min_r;
    height = data->math.max_i - data->math.min_i;
    if (keycode == 4)
        zoom_factor = 0.9;
    else if (keycode == 5)
        zoom_factor = 1.1;
    else {
        return (1);
	}
	width *= zoom_factor;
	height *= zoom_factor;
	data->math.min_r = cx - width / 2.0;
	data->math.max_r = cx + width / 2.0;
	data->math.min_i = cy - height / 2.0;
	data->math.max_i = cy + height / 2.0;
    return (1);
}
