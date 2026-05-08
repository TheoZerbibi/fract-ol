/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simd_burningship.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:00:00 by thzeribi          #+#    #+#             */
/*   Updated: 2026/05/08 14:15:22 by theo             ###   ########.fr       */
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
	ship_simd_step(__m256d *z, __m256d cr, __m256d ci, t_simd_result *res)
{
	__m256d	mask;
	__m256d	abs_m;
	__m256d	sum;

	abs_m = _mm256_castsi256_pd(_mm256_set1_epi64x(0x7FFFFFFFFFFFFFFF));
	z[0] = _mm256_and_pd(z[0], abs_m);
	z[1] = _mm256_and_pd(z[1], abs_m);
	z[1] = _mm256_add_pd(_mm256_mul_pd(
				_mm256_mul_pd(_mm256_set1_pd(2.0), z[0]), z[1]), ci);
	z[0] = _mm256_add_pd(_mm256_sub_pd(z[2], z[3]), cr);
	z[2] = _mm256_mul_pd(z[0], z[0]);
	z[3] = _mm256_mul_pd(z[1], z[1]);
	sum = _mm256_add_pd(z[2], z[3]);
	mask = _mm256_cmp_pd(sum, _mm256_set1_pd(4.0), _CMP_LT_OQ);
	freeze_sq(res, sum, mask);
	if (_mm256_movemask_pd(mask) == 0)
		return (0);
	res->iters = _mm256_add_epi64(res->iters,
			_mm256_and_si256(_mm256_castpd_si256(mask),
				_mm256_set1_epi64x(1)));
	return (1);
}

static inline void
	ship_simd_loop(t_data *d, __m256d cr, __m256d ci, t_simd_result *res)
{
	__m256d	z[4];
	int		i;

	ship_simd_init(z);
	res->sq = _mm256_setzero_pd();
	res->prev_esc = _mm256_setzero_pd();
	i = 0;
	while (i < d->fractal.max_iterations)
	{
		if (!ship_simd_step(z, cr, ci, res))
			break ;
		i++;
	}
}

void
	simd_burningship(t_thread_data *info, int y, double ci)
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
		ship_simd_loop(info->data,
			_mm256_set_pd(crs[3], crs[2], crs[1], crs[0]),
			_mm256_set1_pd(ci), &res);
		extract_smooth_px(&res, info->data->fractal.max_iterations, smooth);
		write_4px(info, x, y, smooth);
		x += 4;
	}
	render_thread_row_remainder(info, y, ci, x);
}
