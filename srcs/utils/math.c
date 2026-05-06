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
