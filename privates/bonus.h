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
# ifndef BONUS_H
# define BONUS_H

# include "fractol.h"
# include <pthread.h>
# include <sched.h>
# include <math.h>

typedef struct s_thread_data	t_thread_data;
typedef int	(*t_inside_func)(double, double);
typedef double	(*t_iterate_func)(t_data *, double, double);

struct s_thread_data
{
	t_data	*data;
	int		start_line;
	int		end_line;
	double	step_r;
	double	step_i;
	int		thread_id;
};

void	set_thread_affinity(int thread_id);
void	*thread_render_generic(void *arg);
void	set_thread_affinity(int thread_id);
void	*thread_render_generic(void *arg);

int		mandelbrot_bonus(t_data *data);
int		burningship_bonus(t_data *data);
int		inside_main_cardioid(double cr, double ci);
int		inside_period2_bulb(double cr, double ci);

# endif
#endif
