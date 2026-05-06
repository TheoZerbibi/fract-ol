/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simd_phoenix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:00:00 by thzeribi          #+#    #+#             */
/*   Updated: 2026/05/06 05:47:32 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

static inline void
	phoenix_simd_init(__m256d *vals, t_data *d, __m256d cr, __m256d ci)
{
	vals[0] = cr;
	vals[1] = ci;
	vals[2] = _mm256_setzero_pd();
	vals[3] = _mm256_setzero_pd();
	vals[4] = _mm256_mul_pd(cr, cr);
	vals[5] = _mm256_mul_pd(ci, ci);
	vals[6] = _mm256_set1_pd(d->fractal.julia_shiftx);
	vals[7] = _mm256_set1_pd(d->fractal.phoenix_p);
}

static inline void
	phoenix_simd_step(__m256d *v)
{
	__m256d	tmp_r;
	__m256d	tmp_i;

	tmp_r = v[0];
	tmp_i = v[1];
	v[1] = _mm256_add_pd(_mm256_mul_pd(
				_mm256_mul_pd(_mm256_set1_pd(2.0), v[0]), v[1]),
			_mm256_mul_pd(v[7], v[3]));
	v[0] = _mm256_add_pd(_mm256_add_pd(
				_mm256_sub_pd(v[4], v[5]), v[6]),
			_mm256_mul_pd(v[7], v[2]));
	v[2] = tmp_r;
	v[3] = tmp_i;
	v[4] = _mm256_mul_pd(v[0], v[0]);
	v[5] = _mm256_mul_pd(v[1], v[1]);
}

static inline void
	phoenix_simd_loop(t_data *d, __m256d cr, __m256d ci,
	__m256i *iters)
{
	__m256d	v[8];
	__m256d	mask;
	int		i;

	phoenix_simd_init(v, d, cr, ci);
	i = 0;
	while (i < d->fractal.max_iterations)
	{
		phoenix_simd_step(v);
		mask = _mm256_cmp_pd(_mm256_add_pd(v[4], v[5]),
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
	simd_phoenix(t_thread_data *info, int y, double ci)
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
		phoenix_simd_loop(info->data,
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
