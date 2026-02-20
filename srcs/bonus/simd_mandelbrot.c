/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simd_mandelbrot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:00:00 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/20 14:00:00 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include "bonus.h"

static inline void
	mandelbrot_simd_loop(t_data *d, __m256d cr, __m256d ci,
	__m256i *iters)
{
	__m256d	zr;
	__m256d	zi;
	__m256d	zr2;
	__m256d	zi2;
	__m256d	four;
	__m256d	mask;
	int		i;

	zr = _mm256_setzero_pd();
	zi = _mm256_setzero_pd();
	zr2 = _mm256_setzero_pd();
	zi2 = _mm256_setzero_pd();
	four = _mm256_set1_pd(4.0);
	i = 0;
	while (i < d->fractal.max_iterations)
	{
		zi = _mm256_add_pd(
				_mm256_mul_pd(_mm256_mul_pd(_mm256_set1_pd(2.0), zr), zi), ci);
		zr = _mm256_add_pd(_mm256_sub_pd(zr2, zi2), cr);
		zr2 = _mm256_mul_pd(zr, zr);
		zi2 = _mm256_mul_pd(zi, zi);
		mask = _mm256_cmp_pd(_mm256_add_pd(zr2, zi2), four, _CMP_LT_OQ);
		if (_mm256_movemask_pd(mask) == 0)
			break;
		*iters =
				_mm256_add_epi64(*iters, _mm256_and_si256(_mm256_castpd_si256(mask),
				_mm256_set1_epi64x(1)));
		i++;
	}
}

static void
	exec_mandelbrot_simd(t_thread_data *info, double *crs, double ci,
	long long int *iters)
{
	__m256d	v_ci;
	__m256d	v_cr;
	__m256i	v_iters;

	v_ci = _mm256_set1_pd(ci);
	v_cr = _mm256_set_pd(crs[3], crs[2], crs[1], crs[0]);
	v_iters = _mm256_setzero_si256();
	mandelbrot_simd_loop(info->data, v_cr, v_ci, &v_iters);
	_mm256_storeu_si256((__m256i *)iters, v_iters);
}

static void
	simd_mandelbrot_row(t_thread_data *info, int y, double ci,
	long long int *it, double *crs)
{
	int	x;
	int	s;

	x = 0;
	while (x <= info->data->win_width - 4)
	{
		crs[0] = info->data->math.min_r + x * info->step_r;
		crs[1] = info->data->math.min_r + (x + 1) * info->step_r;
		crs[2] = info->data->math.min_r + (x + 2) * info->step_r;
		crs[3] = info->data->math.min_r + (x + 3) * info->step_r;
		s = check_main_shapes(crs[0], ci) + check_main_shapes(crs[1], ci) +
				check_main_shapes(crs[2], ci) + check_main_shapes(crs[3], ci);
		if (s == 4)
		{
			it[0] = info->data->fractal.max_iterations;
			it[1] = info->data->fractal.max_iterations;
			it[2] = info->data->fractal.max_iterations;
			it[3] = info->data->fractal.max_iterations;
		}
		else
		{
			exec_mandelbrot_simd(info, crs, ci, it);
			if (check_main_shapes(crs[0], ci))
				it[0] = info->data->fractal.max_iterations;
			if (check_main_shapes(crs[1], ci))
				it[1] = info->data->fractal.max_iterations;
			if (check_main_shapes(crs[2], ci))
				it[2] = info->data->fractal.max_iterations;
			if (check_main_shapes(crs[3], ci))
				it[3] = info->data->fractal.max_iterations;
		}
		put_pixel_simd(info, x, y, it[0]);
		put_pixel_simd(info, x + 1, y, it[1]);
		put_pixel_simd(info, x + 2, y, it[2]);
		put_pixel_simd(info, x + 3, y, it[3]);
		x += 4;
	}
	render_thread_row_remainder(info, y, ci, x);
}

void
	simd_mandelbrot(t_thread_data *info, int y, double ci)
{
	long long int	it[4];
	double			crs[4];

	simd_mandelbrot_row(info, y, ci, it, crs);
}
