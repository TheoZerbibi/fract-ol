/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simd_mandelbrot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:00:00 by thzeribi          #+#    #+#             */
/*   Updated: 2026/05/06 09:18:53 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

static inline void
	mandel_simd_init(__m256d *z)
{
	z[0] = _mm256_setzero_pd();
	z[1] = _mm256_setzero_pd();
	z[2] = _mm256_setzero_pd();
	z[3] = _mm256_setzero_pd();
}

static inline void
	mandelbrot_simd_loop(__m256d cr, __m256d ci, __m256i *iters,
	int max_iter)
{
	__m256d	z[4];
	__m256d	mask;
	int		i;

	mandel_simd_init(z);
	i = 0;
	while (i < max_iter)
	{
		z[1] = _mm256_add_pd(_mm256_mul_pd(
					_mm256_mul_pd(_mm256_set1_pd(2.0), z[0]), z[1]), ci);
		z[0] = _mm256_add_pd(_mm256_sub_pd(z[2], z[3]), cr);
		z[2] = _mm256_mul_pd(z[0], z[0]);
		z[3] = _mm256_mul_pd(z[1], z[1]);
		mask = _mm256_cmp_pd(_mm256_add_pd(z[2], z[3]),
				_mm256_set1_pd(4.0), _CMP_LT_OQ);
		if (_mm256_movemask_pd(mask) == 0)
			break ;
		*iters = _mm256_add_epi64(*iters,
				_mm256_and_si256(_mm256_castpd_si256(mask),
					_mm256_set1_epi64x(1)));
		i++;
	}
}

static void
	fix_cardioid(int *s, long long int *it, int max_iter)
{
	if (s[0])
		it[0] = max_iter;
	if (s[1])
		it[1] = max_iter;
	if (s[2])
		it[2] = max_iter;
	if (s[3])
		it[3] = max_iter;
}

static void
	process_4px(t_thread_data *info, double *crs, double ci,
	long long int *it)
{
	int		s[4];
	__m256i	v_iters;

	s[0] = check_main_shapes(crs[0], ci);
	s[1] = check_main_shapes(crs[1], ci);
	s[2] = check_main_shapes(crs[2], ci);
	s[3] = check_main_shapes(crs[3], ci);
	if (s[0] + s[1] + s[2] + s[3] == 4)
		fix_cardioid(s, it, info->data->fractal.max_iterations);
	else
	{
		v_iters = _mm256_setzero_si256();
		mandelbrot_simd_loop(
			_mm256_set_pd(crs[3], crs[2], crs[1], crs[0]),
			_mm256_set1_pd(ci), &v_iters,
			info->data->fractal.max_iterations);
		_mm256_storeu_si256((__m256i *)it, v_iters);
		fix_cardioid(s, it, info->data->fractal.max_iterations);
	}
}

void
	simd_mandelbrot(t_thread_data *info, int y, double ci)
{
	long long int	it[4];
	double			crs[4];
	int				x;

	x = 0;
	while (x <= info->data->win_width - 4)
	{
		crs[0] = info->data->math.min_r + x * info->step_r;
		crs[1] = crs[0] + info->step_r;
		crs[2] = crs[1] + info->step_r;
		crs[3] = crs[2] + info->step_r;
		process_4px(info, crs, ci, it);
		write_4px(info, x, y, it);
		x += 4;
	}
	render_thread_row_remainder(info, y, ci, x);
}
