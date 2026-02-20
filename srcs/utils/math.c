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

double
	fast_log2(double val)
{
	t_bit_hack	hack;

	hack.d = val;
	return ((double)((hack.i >> 52) - 1023)
		+ (double)(hack.i & 0x000FFFFFFFFFFFFF) / 4503599627370496.0);
}
