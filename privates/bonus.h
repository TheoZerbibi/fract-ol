/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:14:16 by thzeribi          #+#    #+#             */
/*   Updated: 2025/01/05 16:16:27 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
#ifndef BONUS_H
#define BONUS_H

#include "fractol.h"
#include <math.h>
#include <pthread.h>
#include <sched.h>

#define MAX_THREADS 128

typedef struct s_thread_data t_thread_data;

struct s_thread_data {
  t_data *data;
  int start_line;
  int end_line;
  double step_r;
  double step_i;
  int thread_id;
};

void *thread_render_generic(void *arg);
void fill_thread_infos(t_thread_data *info, t_data *data, double *step);
int launch_threads(pthread_t *thr, t_thread_data *info, int n);
int run_threaded_render(t_data *data);

int mandelbrot_bonus(t_data *data);
int burningship_bonus(t_data *data);
int julia_bonus(t_data *data);
int buddhabrot_bonus(t_data *data);
int phoenix_bonus(t_data *data);

#endif
#endif
