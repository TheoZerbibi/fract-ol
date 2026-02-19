/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:14:16 by thzeribi          #+#    #+#             */
/*   Updated: 2025/01/05 16:16:27 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double fast_log2(double val) {
  t_bit_hack hack;

  hack.d = val;
  return ((double)((hack.i >> 52) - 1023) +
          (double)(hack.i & 0x000FFFFFFFFFFFFF) / 4503599627370496.0);
}

static int check_period(double zr, double zi, double *old, int *period) {
  if (zr == old[0] && zi == old[1])
    return (1);
  (*period)++;
  if (*period > 8) {
    old[0] = zr;
    old[1] = zi;
    *period = 0;
  }
  return (0);
}

static double julia_loop(t_data *data, double zr, double zi) {
  double sq[2];
  double old[2];
  int state[2];

  sq[0] = zr * zr;
  sq[1] = zi * zi;
  old[0] = 0.0;
  old[1] = 0.0;
  state[0] = 0;
  state[1] = 0;
  while (sq[0] + sq[1] <= 4.0 && state[0] < data->fractal.max_iterations) {
    zi = 2.0 * zr * zi + data->fractal.julia_shifty;
    zr = sq[0] - sq[1] + data->fractal.julia_shiftx;
    sq[0] = zr * zr;
    sq[1] = zi * zi;
    state[0]++;
    if (check_period(zr, zi, old, &state[1]))
      return ((double)data->fractal.max_iterations);
  }
  if (state[0] == data->fractal.max_iterations)
    return ((double)state[0]);
  return (state[0] + 1 -
          fast_log2(fast_log2(sq[0] + sq[1]) * 0.5) * data->math.log_2);
}

double is_julia(t_data *data, double zr, double zi) {
  return (julia_loop(data, zr, zi));
}

void init_julia(t_data *data) {
  data->math.min_r = -2.0;
  data->math.max_r = 2.0;
  data->math.min_i = -2.0;
  data->math.max_i = 2.0 * (double)data->win_height / (double)data->win_width;
  data->fractal.color_shift = 2;
  data->fractal.resolution_shift = 0;
  data->fractal.max_iterations = MAX_ITER;
  data->math.log_2 = 1.0 / log(2.0);
  data->fractal.iterate = &is_julia;
}
