/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:01:30 by thzeribi          #+#    #+#             */
/*   Updated: 2025/01/05 16:14:44 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

# include "mlx.h"
# include "struct.h"
#ifdef __has_include
# if __has_include("libft.h")
#  include "libft.h"
# endif
#endif
#ifdef BONUS
# include <pthread.h>
#endif
# include "keycodes.h"
# include "define.h"

int		_init_img(t_data *data);
int		_init_mlx(t_data *data);
int		_end_mlx(t_data *data, int err);

void	setup_hook(t_data *data);
int		keypress(int keycode, t_data *datafractol);
int		mouse(int keycode, int x, int y, t_data *data);
void	reset_img(t_data *data);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);


int		draw_usage(t_data *data, int col);
void	usage_background(t_data *data, int color);

void	exit_init(t_data *data);
void	exit_usage(t_data *data);

void	init_mandelbrot(t_data *data);
double  is_mandelbrot_smooth(t_data *data, double cr, double ci);
int		mandelbrot(t_data *data);

void	init_burning_ship(t_data *data);
double  is_burningship_smooth(t_data *data, double cr, double ci);
int	    burning_ship(t_data *data);

#ifdef BONUS
int     mandelbrot_bonus(t_data *data);
int     burningship_bonus(t_data *data);
#endif


#endif
