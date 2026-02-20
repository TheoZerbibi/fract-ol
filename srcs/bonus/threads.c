/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:14:16 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/20 14:00:00 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

static void thread_put_pixel(t_thread_data *info, int x, int y, int color) {
	unsigned int *row;

	row = (unsigned int *)(info->data->image.addr +
												 y * info->data->image.size_line);
	row[x] = color;
}

static void render_thread_row(t_thread_data *info, int y, double ci) {
	int x;
	double cr;
	double it;

	x = 0;
	while (x < info->data->win_width) {
		cr = info->data->math.min_r + x * info->step_r;
		it = info->data->fractal.iterate(info->data, cr, ci);
		if (it >= info->data->fractal.max_iterations)
			thread_put_pixel(info, x, y, create_trgb(0, 0, 0, 0));
		else
			thread_put_pixel(info, x, y, make_color(info->data, it));
		x++;
	}
}

static double get_ci(t_thread_data *info, int y) {
	if (info->data->set == BURNING_SHIP)
		return (info->data->math.min_i + y * info->step_i);
	return (info->data->math.max_i + y * info->step_i);
}

static void dispatch_simd(t_thread_data *info, int y, double ci) {
	if (info->data->set == MANDELBROT)
		simd_mandelbrot(info, y, ci);
	else if (info->data->set == JULIA)
		simd_julia(info, y, ci);
	else if (info->data->set == BURNING_SHIP)
		simd_burningship(info, y, ci);
	else if (info->data->set == PHOENIX)
		simd_phoenix(info, y, ci);
	else
		render_thread_row(info, y, ci);
}

void *thread_render_generic(void *arg) {
	t_thread_data *info;
	int y;
	double ci;

	info = (t_thread_data *)arg;
	set_thread_affinity(info->thread_id);
	y = info->start_line;
	while (y < info->end_line) {
		ci = get_ci(info, y);
		dispatch_simd(info, y, ci);
		y++;
	}
	return (NULL);
}

int run_threaded_render(t_data *data) {
	pthread_t threads[MAX_THREADS];
	t_thread_data infos[MAX_THREADS];
	double step[2];
	int num;

	num = (int)sysconf(_SC_NPROCESSORS_ONLN);
	if (num < 1)
		num = 1;
	if (num > MAX_THREADS)
		num = MAX_THREADS;
	step[0] = (data->math.max_r - data->math.min_r) / (double)data->win_width;
	if (data->set == BURNING_SHIP)
		step[1] = (data->math.max_i - data->math.min_i) / (double)data->win_height;
	else
		step[1] = (data->math.min_i - data->math.max_i) / (double)data->win_height;
	infos[0].thread_id = num;
	fill_thread_infos(infos, data, step);
	return (launch_threads(threads, infos, num));
}

int launch_threads(pthread_t *thr, t_thread_data *info, int n) {
	int i;

	i = 0;
	while (i < n) {
		info[i].thread_id = i;
		if (pthread_create(&thr[i], NULL, thread_render_generic, &info[i]) != 0) {
			while (--i >= 0)
				pthread_join(thr[i], NULL);
			return (FALSE);
		}
		i++;
	}
	i = 0;
	while (i < n) {
		pthread_join(thr[i], NULL);
		i++;
	}
	return (TRUE);
}
