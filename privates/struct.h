/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:18:40 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/19 11:59:16 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <X11/Xlib.h>
# include <X11/extensions/XShm.h>
# include <sys/wait.h>
# include <sys/time.h>
# include "define.h"

typedef struct s_mlx		t_mlx;
typedef struct s_data		t_data;
typedef struct s_img		t_img;
typedef struct s_fractal	t_fractal;
typedef struct s_math		t_math;
typedef struct s_perf		t_perf;
typedef union u_bit_hack	t_bit_hack;
typedef struct s_color		t_color;

struct s_color
{
	int	r;
	int	g;
	int	b;
};

union u_bit_hack
{
	double		d;
	long long	i;
};

typedef struct s_perf
{
	struct timeval	last_time;
	double			fps;
	int				show_debug;
}	t_perf;

typedef struct s_img
{
	void	*image;
	char	*addr;
	int		size_line;
	int		bpp;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_math
{
	double			min_r;
	double			max_r;
	double			min_i;
	double			max_i;
	unsigned int	count;
	double			center_i;
	double			center_r;
}	t_math;

typedef struct s_fractal
{
	int		color_shift;
	int		resolution_shift;
	double	julia_shiftx;
	double	julia_shifty;
	int		julia_locked;
	double	phoenix_p;
	int		max_iterations;
	int		(*draw)(struct s_data *data);
	double	(*iterate)(struct s_data *, double, double);
}	t_fractal;

typedef struct s_data
{
	int					win_width;
	int					win_height;
	int					show_usage;
	int					dirty;
	enum e_fractal_set	set;
	t_mlx				mlx;
	t_img				image;
	t_fractal			fractal;
	t_math				math;
	t_color				color;
	t_perf				perf;
	unsigned int		*histogram;
	unsigned int		hist_max;
}	t_data;

#endif
