/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:18:40 by thzeribi          #+#    #+#             */
/*   Updated: 2025/01/05 19:36:54 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <X11/Xlib.h>
# include <X11/extensions/XShm.h>
# include <sys/wait.h>
# include "define.h"
# include "colors.h"
# ifdef BONUS
#  include "bonus.h"
# include <pthread.h>
# endif

typedef struct s_mlx			t_mlx;
typedef struct s_data			t_data;
typedef struct s_img			t_img;
typedef struct s_color			t_color;
typedef struct s_fractal		t_fractal;
typedef struct s_math			t_math;
typedef struct s_thread_pool	t_thread_pool;

struct s_thread_pool
{
    pthread_mutex_t mutex;
    int             current_line;
    int             total_lines;
    double          step_r;
    double          step_i;
};

typedef struct s_img
{
	void    *image;
	char    *addr;
	int     size_line;
	int     bpp;
	int     endian;
	int     width;
	int     height;
	unsigned int    *buffer;
}   t_img;

typedef struct s_mlx
{
	void    *mlx;
	void    *win;
}   t_mlx;

typedef struct s_math
{
	double          min_r;
	double          max_r;
	double          min_i;
	double          max_i;
	unsigned int    count;
	double          center_i;
	double          center_r;
	double          initial_min_r;
	double          initial_max_r;
	double          initial_min_i;
	double          initial_max_i;
}   t_math;

typedef struct s_fractal
{
	int             color_shift;
	int             resolution_shift;
	double          julia_shiftx;
	double          julia_shifty;
	int             max_iterations;
	double          (*iterate)(struct s_data *data, double cr, double ci);
	int             (*draw)(struct s_data *data);
}   t_fractal;

typedef struct s_data
{
	int         win_width;
	int         win_height;
	int         show_usage;
	enum e_fractal_set set;
	t_mlx       mlx;
	t_img       image;
	t_fractal   fractal;
	t_math      math;
	t_color     color;
#ifdef BONUS
	t_thread_pool thread_pool;
#endif
}   t_data;

#endif
