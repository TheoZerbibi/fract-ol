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


static void
	_zoom(t_math *math, double zoom)
{
	math->center_r = math->min_r - math->max_r;
	math->center_i = math->max_i - math->min_i;
	math->max_r = math->max_r + (math->center_r - zoom * math->center_r) / 2;
	math->min_r = math->max_r + zoom * math->center_r;
	math->min_i = math->min_i + (math->center_i - zoom * math->center_i) / 2;
	math->max_i = math->min_i + zoom * math->center_i;
	return ;
}

int
	mouse(int keycode, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (keycode == 4) {
		_zoom(&data->math, 0.9);
	}
	else if (keycode == 5)
		_zoom(&data->math, 1.1);
	return (1);
}
