/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:14:16 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/19 10:59:08 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void
	draw_fps_line(t_data *d, int col)
{
	char	buf[32];
	int		y;

	y = d->win_height - 130;
	fmt_double(buf, d->perf.fps, 12);
	mlx_string_put(d->mlx.mlx, d->mlx.win, 20, y, col, "FPS:");
	mlx_string_put(d->mlx.mlx, d->mlx.win, 100, y, col, buf);
}

static void
	draw_info_lines(t_data *d, int col)
{
	double	zoom;
	char	buf[32];
	int		y;

	y = d->win_height - 110;
	zoom = INITIAL_ZOOM / (d->math.max_r - d->math.min_r);
	fmt_double(buf, zoom, 12);
	mlx_string_put(d->mlx.mlx, d->mlx.win, 20, y, col, "Zoom:");
	mlx_string_put(d->mlx.mlx, d->mlx.win, 100, y, col, buf);
	y += 20;
	fmt_double(buf, (double)d->fractal.max_iterations, 12);
	mlx_string_put(d->mlx.mlx, d->mlx.win, 20, y, col, "Iter:");
	mlx_string_put(d->mlx.mlx, d->mlx.win, 100, y, col, buf);
}

static void
	draw_center_lines(t_data *d, int col)
{
	char	buf[32];
	int		y;

	y = d->win_height - 50;
	fmt_double(buf, (d->math.min_r + d->math.max_r) * 0.5, 12);
	mlx_string_put(d->mlx.mlx, d->mlx.win, 20, y, col, "cx:");
	mlx_string_put(d->mlx.mlx, d->mlx.win, 100, y, col, buf);
	y += 20;
	fmt_double(buf, (d->math.min_i + d->math.max_i) * 0.5, 12);
	mlx_string_put(d->mlx.mlx, d->mlx.win, 20, y, col, "cy:");
	mlx_string_put(d->mlx.mlx, d->mlx.win, 100, y, col, buf);
}

int
	draw_debug_overlay(t_data *data, int col)
{
	if (!data->perf.show_debug)
		return (0);
	draw_fps_line(data, col);
	draw_info_lines(data, col);
	draw_center_lines(data, col);
	return (0);
}
