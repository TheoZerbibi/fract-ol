/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simd_mandelbrot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:00:00 by thzeribi          #+#    #+#             */
/*   Updated: 2026/05/08 14:16:01 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

static inline void
	mandel_simd_init(__m256d *z, t_simd_result *res)
{
	z[0] = _mm256_setzero_pd();
	z[1] = _mm256_setzero_pd();
	z[2] = _mm256_setzero_pd();
	z[3] = _mm256_setzero_pd();
	res->sq = _mm256_setzero_pd();
	res->prev_esc = _mm256_setzero_pd();
}

static inline void
	mandelbrot_simd_loop(__m256d cr, __m256d ci, t_simd_result *res, int max)
{
	__m256d	z[4];
	__m256d	mask;
	__m256d	sum;
	int		i;

	mandel_simd_init(z, res);
	i = 0;
	while (i < max)
	{
		z[1] = _mm256_add_pd(_mm256_mul_pd(
					_mm256_mul_pd(_mm256_set1_pd(2.0), z[0]), z[1]), ci);
		z[0] = _mm256_add_pd(_mm256_sub_pd(z[2], z[3]), cr);
		z[2] = _mm256_mul_pd(z[0], z[0]);
		z[3] = _mm256_mul_pd(z[1], z[1]);
		sum = _mm256_add_pd(z[2], z[3]);
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

static void
	process_4px(t_thread_data *info, double *crs, double ci, double *smooth)
{
	int				s[4];
	t_simd_result	res;
	int				max;

	max = info->data->fractal.max_iterations;
	s[0] = check_main_shapes(crs[0], ci);
	s[1] = check_main_shapes(crs[1], ci);
	s[2] = check_main_shapes(crs[2], ci);
	s[3] = check_main_shapes(crs[3], ci);
	res.iters = _mm256_setzero_si256();
	mandelbrot_simd_loop(
		_mm256_set_pd(crs[3], crs[2], crs[1], crs[0]),
		_mm256_set1_pd(ci), &res, max);
	extract_smooth_px(&res, max, smooth);
	if (s[0])
		smooth[0] = (double)max;
	if (s[1])
		smooth[1] = (double)max;
	if (s[2])
		smooth[2] = (double)max;
	if (s[3])
		smooth[3] = (double)max;
}

void
	simd_mandelbrot(t_thread_data *info, int y, double ci)
{
	double	smooth[4];
	double	crs[4];
	int		x;

	x = 0;
	while (x <= info->data->win_width - 4)
	{
		crs[0] = info->data->math.min_r + x * info->step_r;
		crs[1] = crs[0] + info->step_r;
		crs[2] = crs[1] + info->step_r;
		crs[3] = crs[2] + info->step_r;
		process_4px(info, crs, ci, smooth);
		write_4px(info, x, y, smooth);
		x += 4;
	}
	render_thread_row_remainder(info, y, ci, x);
}
