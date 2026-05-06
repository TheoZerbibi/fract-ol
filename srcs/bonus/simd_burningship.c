/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simd_burningship.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:00:00 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/20 14:00:00 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

static inline void
	ship_simd_loop(t_data *d, __m256d cr, __m256d ci,
	__m256i *iters)
{
	__m256d	zr;
	__m256d	zi;
	__m256d	zr2;
	__m256d	zi2;
	__m256d	mask;
	int		i;

	zr = _mm256_setzero_pd();
	zi = _mm256_setzero_pd();
	zr2 = _mm256_setzero_pd();
	zi2 = _mm256_setzero_pd();
	i = 0;
	while (i < d->fractal.max_iterations)
	{
		zr = _mm256_and_pd(zr,
				_mm256_castsi256_pd(_mm256_set1_epi64x(0x7FFFFFFFFFFFFFFF)));
		zi = _mm256_and_pd(zi,
				_mm256_castsi256_pd(_mm256_set1_epi64x(0x7FFFFFFFFFFFFFFF)));
		zi = _mm256_add_pd(_mm256_mul_pd(
					_mm256_mul_pd(_mm256_set1_pd(2.0), zr), zi), ci);
		zr = _mm256_add_pd(_mm256_sub_pd(zr2, zi2), cr);
		zr2 = _mm256_mul_pd(zr, zr);
		zi2 = _mm256_mul_pd(zi, zi);
		mask = _mm256_cmp_pd(_mm256_add_pd(zr2, zi2),
				_mm256_set1_pd(4.0), _CMP_LT_OQ);
		if (_mm256_movemask_pd(mask) == 0)
			break ;
		*iters = _mm256_add_epi64(*iters,
				_mm256_and_si256(_mm256_castpd_si256(mask),
				_mm256_set1_epi64x(1)));
		i++;
	}
}

void
	simd_burningship(t_thread_data *info, int y, double ci)
{
	long long int	iters[4];
	double			crs[4];
	__m256i			v_iters;
	int				x;

	x = 0;
	while (x <= info->data->win_width - 4)
	{
		crs[0] = info->data->math.min_r + x * info->step_r;
		crs[1] = crs[0] + info->step_r;
		crs[2] = crs[1] + info->step_r;
		crs[3] = crs[2] + info->step_r;
		v_iters = _mm256_setzero_si256();
		ship_simd_loop(info->data,
			_mm256_set_pd(crs[3], crs[2], crs[1], crs[0]),
			_mm256_set1_pd(ci), &v_iters);
		_mm256_storeu_si256((__m256i *)iters, v_iters);
		put_pixel_simd(info, x, y, iters[0]);
		put_pixel_simd(info, x + 1, y, iters[1]);
		put_pixel_simd(info, x + 2, y, iters[2]);
		put_pixel_simd(info, x + 3, y, iters[3]);
		x += 4;
	}
	render_thread_row_remainder(info, y, ci, x);
}
