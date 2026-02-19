/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:14:16 by thzeribi          #+#    #+#             */
/*   Updated: 2025/01/05 16:16:27 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int julia_mouse_move(int x, int y, t_data *data) {
  double cr;
  double ci;

  if (data->set != JULIA || data->fractal.julia_locked)
    return (0);
  cr = -2.0 + ((double)x / data->win_width) * 4.0;
  ci = -2.0 + ((double)y / data->win_height) * 4.0;
  data->fractal.julia_shiftx = cr;
  data->fractal.julia_shifty = ci;
  return (0);
}
