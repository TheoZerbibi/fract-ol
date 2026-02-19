/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_palette.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:14:16 by thzeribi          #+#    #+#             */
/*   Updated: 2025/01/05 16:16:27 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int nebula_low(double ratio) {
  int r;
  int g;
  int b;

  r = (int)(ratio / 0.25 * 80);
  g = (int)(ratio / 0.25 * 10);
  b = (int)(ratio / 0.25 * 30);
  return (create_trgb(0, r, g, b));
}

static int nebula_mid(double ratio) {
  int r;
  int g;
  int b;
  double t;

  t = (ratio - 0.25) / 0.25;
  r = (int)(80 + t * 140);
  g = (int)(10 + t * 50);
  b = (int)(30 - t * 20);
  return (create_trgb(0, r, g, b));
}

static int nebula_high(double ratio) {
  int r;
  int g;
  int b;
  double t;

  if (ratio < 0.75) {
    t = (ratio - 0.5) / 0.25;
    r = (int)(220 + t * 35);
    g = (int)(60 + t * 120);
    b = (int)(10 + t * 20);
  } else {
    t = (ratio - 0.75) / 0.25;
    r = (int)(255);
    g = (int)(180 + t * 75);
    b = (int)(30 + t * 225);
  }
  return (create_trgb(0, r, g, b));
}

int make_space_color(double ratio) {
  if (ratio < 0.0)
    ratio = 0.0;
  if (ratio > 1.0)
    ratio = 1.0;
  if (ratio < 0.25)
    return (nebula_low(ratio));
  if (ratio < 0.5)
    return (nebula_mid(ratio));
  return (nebula_high(ratio));
}
