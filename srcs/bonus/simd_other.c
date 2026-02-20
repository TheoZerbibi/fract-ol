/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simd_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:00:00 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/20 14:00:00 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include "bonus.h"

static inline void julia_simd_loop(t_data *d, __m256d cr, __m256d ci,
																	 __m256i *iters) {
	__m256d zr;
	__m256d zi;
	__m256d zr2;
	__m256d zi2;
	__m256d c_r;
	__m256d c_i;
	__m256d four;
	__m256d mask;
	int i;

	zr = cr;
	zi = ci;
	zr2 = _mm256_mul_pd(zr, zr);
	zi2 = _mm256_mul_pd(zi, zi);
	c_r = _mm256_set1_pd(d->fractal.julia_shiftx);
	c_i = _mm256_set1_pd(d->fractal.julia_shifty);
	four = _mm256_set1_pd(4.0);
	i = 0;
	while (i < d->fractal.max_iterations) {
		zi = _mm256_add_pd(
				_mm256_mul_pd(_mm256_mul_pd(_mm256_set1_pd(2.0), zr), zi), c_i);
		zr = _mm256_add_pd(_mm256_sub_pd(zr2, zi2), c_r);
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

void simd_julia(t_thread_data *info, int y, double ci) {
	__m256d v_ci;
	__m256d v_cr;
	__m256i v_iters;
	long long int iters[4];
	double crs[4];
	int x;

	v_ci = _mm256_set1_pd(ci);
	x = 0;
	while (x <= info->data->win_width - 4) {
		crs[0] = info->data->math.min_r + x * info->step_r;
		crs[1] = info->data->math.min_r + (x + 1) * info->step_r;
		crs[2] = info->data->math.min_r + (x + 2) * info->step_r;
		crs[3] = info->data->math.min_r + (x + 3) * info->step_r;
		v_cr = _mm256_set_pd(crs[3], crs[2], crs[1], crs[0]);
		v_iters = _mm256_setzero_si256();
		julia_simd_loop(info->data, v_cr, v_ci, &v_iters);
		_mm256_storeu_si256((__m256i *)iters, v_iters);
		put_pixel_simd(info, x, y, iters[0]);
		put_pixel_simd(info, x + 1, y, iters[1]);
		put_pixel_simd(info, x + 2, y, iters[2]);
		put_pixel_simd(info, x + 3, y, iters[3]);
		x += 4;
	}
	render_thread_row_remainder(info, y, ci, x);
}

static inline void burningship_simd_loop(t_data *d, __m256d cr, __m256d ci,
																				 __m256i *iters) {
	__m256d zr;
	__m256d zi;
	__m256d zr2;
	__m256d zi2;
	__m256d four;
	__m256d abs_mask;
	__m256d mask;
	int i;

	zr = _mm256_setzero_pd();
	zi = _mm256_setzero_pd();
	zr2 = _mm256_setzero_pd();
	zi2 = _mm256_setzero_pd();
	four = _mm256_set1_pd(4.0);
	abs_mask = _mm256_castsi256_pd(_mm256_set1_epi64x(0x7FFFFFFFFFFFFFFF));
	i = 0;
	while (i < d->fractal.max_iterations) {
		zi = _mm256_add_pd(_mm256_mul_pd(_mm256_mul_pd(_mm256_set1_pd(2.0),
																									 _mm256_and_pd(zr, abs_mask)),
																		 _mm256_and_pd(zi, abs_mask)),
											 ci);
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

void simd_burningship(t_thread_data *info, int y, double ci) {
	__m256d v_ci;
	__m256d v_cr;
	__m256i v_iters;
	long long int iters[4];
	double crs[4];
	int x;

	v_ci = _mm256_set1_pd(ci);
	x = 0;
	while (x <= info->data->win_width - 4) {
		crs[0] = info->data->math.min_r + x * info->step_r;
		crs[1] = info->data->math.min_r + (x + 1) * info->step_r;
		crs[2] = info->data->math.min_r + (x + 2) * info->step_r;
		crs[3] = info->data->math.min_r + (x + 3) * info->step_r;
		v_cr = _mm256_set_pd(crs[3], crs[2], crs[1], crs[0]);
		v_iters = _mm256_setzero_si256();
		burningship_simd_loop(info->data, v_cr, v_ci, &v_iters);
		_mm256_storeu_si256((__m256i *)iters, v_iters);
		put_pixel_simd(info, x, y, iters[0]);
		put_pixel_simd(info, x + 1, y, iters[1]);
		put_pixel_simd(info, x + 2, y, iters[2]);
		put_pixel_simd(info, x + 3, y, iters[3]);
		x += 4;
	}
	render_thread_row_remainder(info, y, ci, x);
}

static inline void phoenix_simd_loop(t_data *d, __m256d cr, __m256d ci,
																		 __m256i *iters) {
	__m256d zr;
	__m256d zi;
	__m256d p_r;
	__m256d p_i;
	__m256d zr2;
	__m256d zi2;
	__m256d sx;
	__m256d pp;
	__m256d four;
	__m256d mask;
	__m256d tmp_r;
	__m256d tmp_i;
	int i;

	zr = cr;
	zi = ci;
	p_r = _mm256_setzero_pd();
	p_i = _mm256_setzero_pd();
	zr2 = _mm256_mul_pd(zr, zr);
	zi2 = _mm256_mul_pd(zi, zi);
	sx = _mm256_set1_pd(d->fractal.julia_shiftx);
	pp = _mm256_set1_pd(d->fractal.phoenix_p);
	four = _mm256_set1_pd(4.0);
	i = 0;
	while (i < d->fractal.max_iterations) {
		tmp_r = zr;
		tmp_i = zi;
		zi =
				_mm256_add_pd(_mm256_mul_pd(_mm256_mul_pd(_mm256_set1_pd(2.0), zr), zi),
											_mm256_mul_pd(pp, p_i));
		zr = _mm256_add_pd(_mm256_add_pd(_mm256_sub_pd(zr2, zi2), sx),
											 _mm256_mul_pd(pp, p_r));
		p_r = tmp_r;
		p_i = tmp_i;
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

void simd_phoenix(t_thread_data *info, int y, double ci) {
	__m256d v_ci;
	__m256d v_cr;
	__m256i v_iters;
	long long int iters[4];
	double crs[4];
	int x;

	v_ci = _mm256_set1_pd(ci);
	x = 0;
	while (x <= info->data->win_width - 4) {
		crs[0] = info->data->math.min_r + x * info->step_r;
		crs[1] = info->data->math.min_r + (x + 1) * info->step_r;
		crs[2] = info->data->math.min_r + (x + 2) * info->step_r;
		crs[3] = info->data->math.min_r + (x + 3) * info->step_r;
		v_cr = _mm256_set_pd(crs[3], crs[2], crs[1], crs[0]);
		v_iters = _mm256_setzero_si256();
		phoenix_simd_loop(info->data, v_cr, v_ci, &v_iters);
		_mm256_storeu_si256((__m256i *)iters, v_iters);
		put_pixel_simd(info, x, y, iters[0]);
		put_pixel_simd(info, x + 1, y, iters[1]);
		put_pixel_simd(info, x + 2, y, iters[2]);
		put_pixel_simd(info, x + 3, y, iters[3]);
		x += 4;
	}
	render_thread_row_remainder(info, y, ci, x);
}
