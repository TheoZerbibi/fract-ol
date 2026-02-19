/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_overlay.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:14:16 by thzeribi          #+#    #+#             */
/*   Updated: 2025/01/05 16:16:27 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void update_fps(t_data *data) {
  struct timeval now;
  double delta;

  gettimeofday(&now, NULL);
  delta = (now.tv_sec - data->perf.last_time.tv_sec) +
          (now.tv_usec - data->perf.last_time.tv_usec) / 1000000.0;
  if (delta > 0.0)
    data->perf.fps = 1.0 / delta;
  data->perf.last_time = now;
}

void debug_background(t_data *data, int color) {
  int i;
  int j;

  i = 10;
  while (i < 280) {
    j = data->win_height - 140;
    while (j < data->win_height - 10) {
      my_mlx_pixel_put(&(data->image), i, j, color);
      j++;
    }
    i++;
  }
}

void fmt_double(char *dst, double val, int size) {
  int whole;
  int frac;
  int i;

  whole = (int)val;
  if (val < 0)
    frac = (int)((-val - (-whole)) * 100);
  else
    frac = (int)((val - whole) * 100);
  i = 0;
  while (i < size)
    dst[i++] = ' ';
  dst[size] = '\0';
  i = size - 1;
  dst[i--] = '0' + frac % 10;
  dst[i--] = '0' + frac / 10;
  dst[i--] = '.';
  if (whole == 0)
    dst[i--] = '0';
  while (whole > 0 && i >= 0) {
    dst[i--] = '0' + whole % 10;
    whole /= 10;
  }
  if (val < 0 && i >= 0)
    dst[i] = '-';
}
