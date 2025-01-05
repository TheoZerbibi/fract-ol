/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 05:39:15 by thzeribi          #+#    #+#             */
/*   Updated: 2025/01/05 06:54:37 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

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
	double width;
	double height;
	double zoom_factor;

	cx = data->math.min_r + ((double)x * (data->math.max_r - data->math.min_r)) / data->win_width;
	if (data->set == BURNING_SHIP)
		cy = data->math.min_i + ((double)y * (data->math.max_i - data->math.min_i)) / data->win_height;
	else
		cy = data->math.max_i - ((double)y * (data->math.max_i - data->math.min_i)) / data->win_height;
	width = data->math.max_r - data->math.min_r;
	height = data->math.max_i - data->math.min_i;
	if (keycode == 4)
		zoom_factor = 0.9;
	else if (keycode == 5)
		zoom_factor = 1.1;
	else
		return (1);
	data->math.min_r = cx - (cx - data->math.min_r) * zoom_factor;
	data->math.max_r = cx + (data->math.max_r - cx) * zoom_factor;
	data->math.min_i = cy - (cy - data->math.min_i) * zoom_factor;
	data->math.max_i = cy + (data->math.max_i - cy) * zoom_factor;
	return (1);
}
