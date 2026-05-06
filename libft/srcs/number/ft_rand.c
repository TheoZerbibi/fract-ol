/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 04:00:00 by thzeribi          #+#    #+#             */
/*   Updated: 2026/05/06 05:44:22 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/time.h>

#define LCG_MUL 1664525UL
#define LCG_INC 1013904223UL

static int
	seed_from_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((int)((unsigned long)tv.tv_sec * 1000000UL
		+ (unsigned long)tv.tv_usec));
}

int
	ft_rand(void)
{
	static __thread unsigned long	state = 0;
	static __thread int				seeded = 0;

	if (!seeded)
	{
		state = (unsigned long)seed_from_time();
		seeded = 1;
	}
	state = state * LCG_MUL + LCG_INC;
	return ((int)((state >> 1) & 0x7FFFFFFF));
}
