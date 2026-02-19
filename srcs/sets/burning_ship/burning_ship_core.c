/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship_core.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:44:50 by thzeribi          #+#    #+#             */
/*   Updated: 2024/02/21 10:44:50 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void apply_abs_hack(double *val) {
  t_bit_hack hack;

  hack.d = *val;
  hack.i &= 0x7FFFFFFFFFFFFFFF;
  *val = hack.d;
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

static double fast_log2(double val) {
  t_bit_hack hack;

  hack.d = val;
  return ((double)((hack.i >> 52) - 1023) +
          (double)(hack.i & 0x000FFFFFFFFFFFFF) / 4503599627370496.0);
}

static double ship_loop(t_data *data, double cr, double ci) {
  double z[2];
  double sq[2];
  double old[2];
  int state[2];

  z[0] = 0.0;
  z[1] = 0.0;
  sq[0] = 0.0;
  sq[1] = 0.0;
  old[0] = 0.0;
  old[1] = 0.0;
  state[0] = 0;
  state[1] = 0;
  while (sq[0] + sq[1] <= 4.0 && state[0] < data->fractal.max_iterations) {
    apply_abs_hack(&z[0]);
    apply_abs_hack(&z[1]);
    z[1] = 2.0 * z[0] * z[1] + ci;
    z[0] = sq[0] - sq[1] + cr;
    sq[0] = z[0] * z[0];
    sq[1] = z[1] * z[1];
    state[0]++;
    if (check_period(z[0], z[1], old, &state[1]))
      return ((double)data->fractal.max_iterations);
  }
  if (state[0] == data->fractal.max_iterations)
    return ((double)state[0]);
  return (state[0] + 1 -
          fast_log2(fast_log2(sq[0] + sq[1]) * 0.5) * data->math.log_2);
}

double is_burning_ship(t_data *data, double cr, double ci) {
  return (ship_loop(data, cr, ci));
}

void init_burning_ship(t_data *data) {
  data->math.min_r = -2.0;
  data->math.max_r = 1.0;
  data->math.min_i = -2.0;
  data->math.max_i = 2.0;
  data->fractal.color_shift = 3;
  data->fractal.max_iterations = MAX_ITER;
  data->fractal.resolution_shift = 0;
  data->math.log_2 = 1.0 / log(2.0);
  data->fractal.iterate = &is_burning_ship;
}
