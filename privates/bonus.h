/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:14:16 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/19 12:17:56 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include "fractol.h"

# include <immintrin.h>
# include <pthread.h>
# include <sched.h>

# define MAX_THREADS	128

typedef struct s_thread_data	t_thread_data;

struct s_thread_data
{
	t_data	*data;
	int		start_line;
	int		end_line;
	int		thread_id;
	double	step_r;
	double	step_i;
};

void	set_thread_affinity(int thread_id);
void	*thread_render_generic(void *arg);
void	fill_thread_infos(t_thread_data *info, t_data *data, double *step);
void	sample_buddhabrot(t_data *data, int num_samples);
int		launch_threads(pthread_t *thr, t_thread_data *info, int n);
int		run_threaded_render(t_data *data);
int		mandelbrot_bonus(t_data *data);
int		burningship_bonus(t_data *data);
int		julia_bonus(t_data *data);
int		buddhabrot_bonus(t_data *data);
int		phoenix_bonus(t_data *data);

void	put_pixel_simd(t_thread_data *info, int x, int y, long long it);
void	render_thread_row_remainder(t_thread_data *info,
			int y, double ci, int x);
void	simd_mandelbrot(t_thread_data *info, int y, double ci);
void	simd_julia(t_thread_data *info, int y, double ci);
void	simd_burningship(t_thread_data *info, int y, double ci);
void	simd_phoenix(t_thread_data *info, int y, double ci);

#endif
