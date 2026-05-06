/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:14:16 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/19 10:17:22 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int
	julia_mouse_move(int x, int y, t_data *data)
{
	double	cr;
	double	ci;

	if (data->set != JULIA || data->fractal.julia_locked)
		return (0);
	cr = JULIA_MIN + ((double)x / data->win_width) * JULIA_RANGE;
	ci = JULIA_MIN + ((double)y / data->win_height) * JULIA_RANGE;
	data->fractal.julia_shiftx = cr;
	data->fractal.julia_shifty = ci;
	data->dirty = 1;
	return (0);
}
