/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:01:30 by mjacquet          #+#    #+#             */
/*   Updated: 2024/02/22 07:56:25 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "mlx.h"
# include "struct.h"
# include "libft.h"
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
int		create_trgb(int t, int r, int g, int b);
int		make_color(t_data *data);
void	change_color_shift(t_data *data);

int		draw_usage(t_data *data, int col);
void	usage_background(t_data *data, int color);

void	exit_init(t_data *data);
void	exit_usage(t_data *data);

void	init_mandelbrot(t_data *data);
int		mandelbrot(t_data *data);

#endif
