/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:18:40 by mjacquet          #+#    #+#             */
/*   Updated: 2024/02/23 06:32:41 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <X11/Xlib.h>
# include <X11/extensions/XShm.h>
# include <sys/wait.h>
# include "define.h"

typedef struct s_mlx		t_mlx;
typedef struct s_data		t_data;
typedef struct s_img		t_img;
typedef struct s_color		t_color;
typedef struct s_fractal	t_fractal;
typedef struct s_math		t_math;

struct s_img
{
	void	*image;
	char	*addr;
	int		size_line;
	int		bpp;
	int		endian;
	int		width;
	int		height;
};

struct s_mlx
{
	void	*mlx;
	void	*win;
};

struct s_color
{
	int	r;
	int	g;
	int	b;
	int	t;
};

struct s_math
{
	double			min_r;
	double			max_r;
	double			min_i;
	double			max_i;
	unsigned int	count;
	double			center_i;
	double			center_r;
};

struct s_fractal
{
	int				color_shift;
	int				resolution_shift;
	double			julia_shiftx;
	double			julia_shifty;
	int				(*draw)(t_data *data);
};

struct s_data
{
	int					win_width;
	int					win_height;
	int					show_usage;
	double				min_r;
	enum e_fractal_set	set;
	t_mlx				mlx;
	t_img				image;
	t_fractal			fractal;
	t_math				math;
	t_color				color;
};

#endif
