/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simd_burningship.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:00:00 by thzeribi          #+#    #+#             */
/*   Updated: 2026/05/06 09:27:32 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

static inline void
	ship_simd_init(__m256d *z)
{
	z[0] = _mm256_setzero_pd();
	z[1] = _mm256_setzero_pd();
	z[2] = _mm256_setzero_pd();
	z[3] = _mm256_setzero_pd();
}

static inline int
	ship_simd_step(__m256d *z, __m256d cr, __m256d ci, __m256i *iters)
{
	__m256d	mask;

	z[0] = _mm256_and_pd(z[0],
			_mm256_castsi256_pd(_mm256_set1_epi64x(0x7FFFFFFFFFFFFFFF)));
	z[1] = _mm256_and_pd(z[1],
			_mm256_castsi256_pd(_mm256_set1_epi64x(0x7FFFFFFFFFFFFFFF)));
	z[1] = _mm256_add_pd(_mm256_mul_pd(
				_mm256_mul_pd(_mm256_set1_pd(2.0), z[0]), z[1]), ci);
	z[0] = _mm256_add_pd(_mm256_sub_pd(z[2], z[3]), cr);
	z[2] = _mm256_mul_pd(z[0], z[0]);
	z[3] = _mm256_mul_pd(z[1], z[1]);
	mask = _mm256_cmp_pd(_mm256_add_pd(z[2], z[3]),
			_mm256_set1_pd(4.0), _CMP_LT_OQ);
	if (_mm256_movemask_pd(mask) == 0)
		return (0);
	*iters = _mm256_add_epi64(*iters,
			_mm256_and_si256(_mm256_castpd_si256(mask),
				_mm256_set1_epi64x(1)));
	return (1);
}

static inline void
	ship_simd_loop(t_data *d, __m256d cr, __m256d ci,
	__m256i *iters)
{
	__m256d	z[4];
	int		i;

	ship_simd_init(z);
	i = 0;
	while (i < d->fractal.max_iterations)
	{
		if (!ship_simd_step(z, cr, ci, iters))
			break ;
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
