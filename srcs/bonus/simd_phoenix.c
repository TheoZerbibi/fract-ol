/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simd_phoenix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:00:00 by thzeribi          #+#    #+#             */
/*   Updated: 2026/05/08 14:15:37 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

static inline void
	phoenix_simd_init(__m256d *v, t_data *d, __m256d cr, __m256d ci)
{
	v[0] = cr;
	v[1] = ci;
	v[2] = _mm256_setzero_pd();
	v[3] = _mm256_setzero_pd();
	v[4] = _mm256_mul_pd(cr, cr);
	v[5] = _mm256_mul_pd(ci, ci);
	v[6] = _mm256_set1_pd(d->fractal.julia_shiftx);
	v[7] = _mm256_set1_pd(d->fractal.phoenix_p);
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
	phoenix_simd_loop(t_data *d, __m256d cr, __m256d ci, t_simd_result *res)
{
	__m256d	v[8];
	__m256d	mask;
	__m256d	sum;
	int		i;

	phoenix_simd_init(v, d, cr, ci);
	res->sq = _mm256_setzero_pd();
	res->prev_esc = _mm256_setzero_pd();
	i = 0;
	while (i < d->fractal.max_iterations)
	{
		phoenix_simd_step(v);
		sum = _mm256_add_pd(v[4], v[5]);
		mask = _mm256_cmp_pd(sum, _mm256_set1_pd(4.0), _CMP_LT_OQ);
		freeze_sq(res, sum, mask);
		if (_mm256_movemask_pd(mask) == 0)
			break ;
		res->iters = _mm256_add_epi64(res->iters,
				_mm256_and_si256(_mm256_castpd_si256(mask),
					_mm256_set1_epi64x(1)));
		i++;
	}
}

void
	simd_phoenix(t_thread_data *info, int y, double ci)
{
	double			smooth[4];
	double			crs[4];
	t_simd_result	res;
	int				x;

	x = 0;
	while (x <= info->data->win_width - 4)
	{
		crs[0] = info->data->math.min_r + x * info->step_r;
		crs[1] = crs[0] + info->step_r;
		crs[2] = crs[1] + info->step_r;
		crs[3] = crs[2] + info->step_r;
		res.iters = _mm256_setzero_si256();
		phoenix_simd_loop(info->data,
			_mm256_set_pd(crs[3], crs[2], crs[1], crs[0]),
			_mm256_set1_pd(ci), &res);
		extract_smooth_px(&res, info->data->fractal.max_iterations, smooth);
		write_4px(info, x, y, smooth);
		x += 4;
	}
	render_thread_row_remainder(info, y, ci, x);
}
