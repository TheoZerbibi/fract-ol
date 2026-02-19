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
# ifdef __has_include
#  if __has_include("libft.h")
#   include "libft.h"
#  endif
# endif
# include "keycodes.h"
# include "define.h"

int		_init_img(t_data *data);
int		_init_mlx(t_data *data);
int		_end_mlx(t_data *data, int err);

void	setup_hook(t_data *data);
int		keypress(int keycode, t_data *datafractol);
int		mouse(int keycode, int x, int y, t_data *data);
int		julia_mouse_move(int x, int y, t_data *data);
void	reset_img(t_data *data);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);

int		draw_usage(t_data *data, int col);
void	usage_background(t_data *data, int color);

void	exit_init(t_data *data);
void	exit_usage(t_data *data);

double	lerp(double a, double b, double t);
t_color	interpolate(t_color c1, t_color c2, double t);
int		create_trgb(int t, int r, int g, int b);
int		clamp_color(int c);
int		make_color(t_data *data, double iteration);
void	change_color_shift(t_data *data);
int		init_fractol_set(char *set, t_data *data);

void	init_mandelbrot(t_data *data);
double	is_mandelbrot(t_data *data, double cr, double ci);
int		check_main_shapes(double cr, double ci);
int		mandelbrot(t_data *data);

void	init_burning_ship(t_data *data);
double	is_burning_ship(t_data *data, double cr, double ci);
int		burning_ship(t_data *data);

void	init_julia(t_data *data);
double	is_julia(t_data *data, double zr, double zi);
int		julia(t_data *data);

void	init_buddhabrot(t_data *data);
int		buddhabrot(t_data *data);

void	init_phoenix(t_data *data);
double	is_phoenix(t_data *data, double cr, double ci);
int		phoenix(t_data *data);

void	update_fps(t_data *data);
void	debug_background(t_data *data, int color);
int		draw_debug_overlay(t_data *data, int col);
void	update_adaptive_iter(t_data *data);

# ifdef BONUS

int		mandelbrot_bonus(t_data *data);
int		burningship_bonus(t_data *data);
int		julia_bonus(t_data *data);
int		buddhabrot_bonus(t_data *data);
int		phoenix_bonus(t_data *data);
# endif

#endif
