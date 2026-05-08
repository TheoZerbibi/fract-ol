/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:43:01 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/19 11:44:47 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @brief    Fast approximate log2 using IEEE 754 bit manipulation.
 *
 * Extracts the exponent and mantissa fields from the double's binary
 * representation to compute an approximation of log2 without calling
 * the standard library log function.
 *
 * @param    val   Input value (must be positive).
 * @return   Approximate log2(val).
 * @note     Uses union t_bit_hack to reinterpret double bits as long long.
 *           Exponent: bits 52-62 (biased by 1023). Mantissa: bits 0-51.
 */
double
	fast_log2(double val)
{
	t_bit_hack	hack;

	hack.d = val;
	return ((double)((hack.i >> 52) - 1023)
		+ (double)(hack.i & 0x000FFFFFFFFFFFFF) / 4503599627370496.0);
}

/**
 * @brief    Detect orbital period to accelerate bounded-point detection.
 *
 * @param    zr      Current real part of z.
 * @param    zi      Current imaginary part of z.
 * @param    old     Saved reference orbit point (updated every 8 steps).
 * @param    period  Step counter since last reference update.
 * @return   1 if cycle detected (point is bounded), 0 otherwise.
 */
int
	check_period(double zr, double zi, double *old, int *period)
{
	if (zr == old[0] && zi == old[1])
		return (1);
	(*period)++;
	if (*period > 8)
	{
		old[0] = zr;
		old[1] = zi;
		*period = 0;
	}
	return (0);
}
