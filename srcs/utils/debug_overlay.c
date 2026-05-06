/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_overlay.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:14:16 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/19 11:20:42 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int
	write_whole(char *dst, int w, int i)
{
	if (w == 0)
		dst[i--] = '0';
	while (w > 0 && i >= 0)
	{
		dst[i--] = '0' + (w % 10);
		w /= 10;
	}
	return (i);
}

void
	update_fps(t_data *data)
{
	struct timeval	now;
	double			delta;

	gettimeofday(&now, NULL);
	delta = (now.tv_sec - data->perf.last_time.tv_sec)
		+ (now.tv_usec - data->perf.last_time.tv_usec) / 1000000.0;
	if (delta > 0.0)
		data->perf.fps = 1.0 / delta;
	data->perf.last_time = now;
}

void
	debug_background(t_data *data, int color)
{
	int	i;
	int	j;

	i = 10;
	while (i < 280)
	{
		j = data->win_height - 140;
		while (j < data->win_height - 10)
		{
			my_mlx_pixel_put(&(data->image), i, j, color);
			j++;
		}
		i++;
	}
}

void
	fmt_double(char *dst, double val, int size)
{
	double	abs_val;
	int		w;
	int		f;
	int		i;

	if (val < 0)
		abs_val = -val;
	else
		abs_val = val;
	w = (int)abs_val;
	f = (int)((abs_val - w) * 100);
	i = size;
	dst[i--] = '\0';
	while (i >= 0)
		dst[i--] = ' ';
	i = size - 1;
	dst[i--] = '0' + (f % 10);
	dst[i--] = '0' + (f / 10);
	dst[i--] = '.';
	i = write_whole(dst, w, i);
	if (val < 0 && i >= 0)
		dst[i] = '-';
}
