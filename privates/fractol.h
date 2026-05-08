/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:01:30 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/19 16:20:57 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <unistd.h>
# include <stdlib.h>

# include "mlx.h"
# include "struct.h"
# ifdef __has_include
#  if __has_include("libft.h")
#   include "libft.h"
#  endif
# endif
# include "keycodes.h"
# include "define.h"

int		init_img(t_data *data);
int		init_mlx(t_data *data);
int		end_mlx(t_data *data, int err);
int		keypress(int keycode, t_data *datafractol);
int		mouse(int keycode, int x, int y, t_data *data);
int		julia_mouse_move(int x, int y, t_data *data);
int		draw_usage(t_data *data, int col);
int		create_trgb(int t, int r, int g, int b);
int		clamp_color(int c);
int		make_color(t_data *data, double iteration);
int		init_fractol_set(char *set, t_data *data);
int		check_main_shapes(double cr, double ci);
int		mandelbrot(t_data *data);
int		burning_ship(t_data *data);
int		julia(t_data *data);
int		phoenix(t_data *data);
int		buddhabrot(t_data *data);
int		draw_debug_overlay(t_data *data, int col);
int		make_space_color(double ratio);
int		render_set(t_data *data);
int		check_period(double zr, double zi, double *old, int *period);
double	fast_log2(double val);
double	lerp(double a, double b, double t);
double	is_mandelbrot(t_data *data, double cr, double ci);
void	setup_hook(t_data *data);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void	reset_img(t_data *data);
void	exit_init(t_data *data);
void	exit_usage(t_data *data);
void	usage_background(t_data *data, int color);
void	change_color_shift(t_data *data);
void	init_mandelbrot(t_data *data);
void	init_burning_ship(t_data *data);
void	init_julia(t_data *data);
void	init_buddhabrot(t_data *data);
void	init_phoenix(t_data *data);
void	update_fps(t_data *data);
void	debug_background(t_data *data, int color);
void	update_adaptive_iter(t_data *data);
void	fmt_double(char *dst, double val, int size);
void	sample_buddhabrot(t_data *data, int num_samples);
t_color	interpolate(t_color c1, t_color c2, double t);

#endif
