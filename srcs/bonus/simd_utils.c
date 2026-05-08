/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simd_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:00:00 by thzeribi          #+#    #+#             */
/*   Updated: 2026/05/08 10:00:00 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

/**
 * @file    simd_utils.c
 * @brief   SIMD pixel write helpers for the multithreaded bonus renderer.
 *
 * SIMD — Single Instruction, Multiple Data — is a CPU feature that lets
 * one instruction operate on several values at the same time.
 * This project uses AVX2 (256-bit registers) to process 4 double-precision
 * pixels per clock cycle instead of 1.
 *
 * Without SIMD (scalar — CPU executes ADD 4 separate times):
 * @code
 * for (int i = 0; i < 4; i++)
 *     result[i] = a[i] + b[i];
 * @endcode
 *
 * With SIMD AVX2 (4 additions in a single CPU instruction):
 * @code
 * __m256d vec_a      = _mm256_loadu_pd(a);
 * __m256d vec_b      = _mm256_loadu_pd(b);
 * __m256d vec_result = _mm256_add_pd(vec_a, vec_b);
 * _mm256_storeu_pd(result, vec_result);
 * @endcode
 *
 * Instead of iterating z = z^2 + c for one pixel at a time, each SIMD pass
 * loads 4 adjacent pixels into __m256d registers and runs the recurrence on
 * all 4 simultaneously. freeze_sq() captures |z|^2 at the exact escape moment
 * per lane, enabling compute_smooth() to apply the normalized iteration count
 * algorithm for band-free coloring.
 *
 * Theoretical gain: 4x. Practical gain: ~3-3.5x, because the loop must wait
 * for the slowest pixel in each batch before advancing.
 */

/**
 * @brief    Freeze per-lane |z|^2 at the first moment of escape.
 *
 * Derives the escape mask from the complement of @p bounded (the LT mask
 * already computed in the caller), avoiding redundant SIMD ops.
 *
 * @param    res      SIMD result struct (writes sq and prev_esc).
 * @param    sum      Pre-computed zr^2 + zi^2 for all 4 lanes.
 * @param    bounded  The LT mask from the caller (1 = still bounded).
 */
void
	freeze_sq(t_simd_result *res, __m256d sum, __m256d bounded)
{
	__m256d	esc;
	__m256d	newly;
	__m256d	ones;

	ones = _mm256_castsi256_pd(_mm256_set1_epi64x(-1));
	esc = _mm256_andnot_pd(bounded, ones);
	newly = _mm256_andnot_pd(res->prev_esc, esc);
	res->sq = _mm256_blendv_pd(res->sq, sum, newly);
	res->prev_esc = _mm256_or_pd(res->prev_esc, newly);
}

/**
 * @brief    Convert 4 integer escape counts + frozen moduli to smooth values.
 *
 * Applies: smooth = iter + 1 - log2(log2(|z|^2) * 0.5) per lane.
 * Points inside the set (it >= max) are assigned (double)max as sentinel.
 * Result is clamped to >= 0 to prevent NaN from reaching palette lookup.
 *
 * @param    it    Array of 4 integer iteration counts.
 * @param    sq    Array of 4 frozen |z|^2 values at escape.
 * @param    max   max_iterations threshold.
 * @param    out   Output array of 4 smooth iteration values.
 */
void
	compute_smooth(long long *it, double *sq, int max, double *out)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (it[i] >= max)
			out[i] = (double)max;
		else
			out[i] = (double)it[i] + 1.0
				- fast_log2(fast_log2(sq[i]) * 0.5);
		if (out[i] < 0.0)
			out[i] = 0.0;
		i++;
	}
}

/**
 * @brief    Extract 4 smooth iteration values from SIMD result.
 *
 * @param    res     SIMD result struct with iteration counts and frozen |z|^2.
 * @param    max     max_iterations threshold.
 * @param    smooth  Output array of 4 smooth iteration values.
 */
void
	extract_smooth_px(t_simd_result *res, int max, double *smooth)
{
	long long	it[4];
	double		sq[4];

	_mm256_storeu_si256((__m256i *)it, res->iters);
	_mm256_storeu_pd(sq, res->sq);
	compute_smooth(it, sq, max, smooth);
}

void
	render_thread_row_remainder(t_thread_data *info,
	int y, double ci, int x)
{
	double			cr;
	double			it;
	unsigned int	*row;

	row = (unsigned int *)(info->data->image.addr
			+ y * info->data->image.size_line);
	while (x < info->data->win_width)
	{
		cr = info->data->math.min_r + x * info->step_r;
		it = info->data->fractal.iterate(info->data, cr, ci);
		if (it >= info->data->fractal.max_iterations)
			row[x] = 0;
		else
			row[x] = make_color(info->data, it);
		x++;
	}
}

/**
 * @brief    Write 4 SIMD-computed pixels to the image buffer.
 *
 * @param    info    Thread context.
 * @param    x       Starting x-coordinate (pixels x, x+1, x+2, x+3 written).
 * @param    y       Row y-coordinate.
 * @param    smooth  Array of 4 smooth iteration values.
 */
void
	write_4px(t_thread_data *info, int x, int y, double *smooth)
{
	unsigned int	*row;
	int				i;
	int				max;

	row = (unsigned int *)(info->data->image.addr
			+ y * info->data->image.size_line);
	max = info->data->fractal.max_iterations;
	i = 0;
	while (i < 4)
	{
		if (smooth[i] >= (double)max)
			row[x + i] = 0;
		else
			row[x + i] = make_color(info->data, smooth[i]);
		i++;
	}
}
