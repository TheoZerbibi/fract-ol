/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:44:50 by thzeribi          #+#    #+#             */
/*   Updated: 2024/02/21 10:44:50 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int check_main_shapes(double cr, double ci) {
  double i2;
  double tr;
  double q;

  i2 = ci * ci;
  tr = cr - 0.25;
  q = tr * tr + i2;
  if (q * (q + tr) <= 0.25 * i2)
    return (1);
  tr = cr + 1.0;
  if (tr * tr + i2 <= 0.0625)
    return (1);
  return (0);
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

static double mandelbrot_loop(t_data *data, double cr, double ci) {
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

double is_mandelbrot(t_data *data, double cr, double ci) {
  if (check_main_shapes(cr, ci))
    return ((double)data->fractal.max_iterations);
  return (mandelbrot_loop(data, cr, ci));
}

void init_mandelbrot(t_data *data) {
  data->math.min_r = -2.0;
  data->math.max_r = 2.0;
  data->math.min_i = -2.0;
  data->math.max_i = 2.0 * (double)data->win_height / (double)data->win_width;
  data->fractal.color_shift = 1;
  data->fractal.resolution_shift = 0;
  data->fractal.max_iterations = MAX_ITER;
  data->math.log_2 = 1.0 / log(2.0);
  data->fractal.iterate = &is_mandelbrot;
}
