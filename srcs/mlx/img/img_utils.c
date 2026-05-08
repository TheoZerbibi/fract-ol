/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 21:13:32 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/19 10:26:03 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void
	my_mlx_pixel_put(t_img *image, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return ;
	dst = image->addr + (y * image->size_line + x * (image->bpp / 8));
	*(unsigned int *)dst = color;
}

void
	reset_img(t_data *data)
{
	ft_memset(data->image.addr, 0,
		data->image.size_line * data->image.height);
}

static void
	render_row(t_data *data, unsigned int *row, int y, double *step)
{
	int		x;
	double	ci;
	double	it;

	if (data->set == BURNING_SHIP)
		ci = data->math.min_i + y * step[1];
	else
		ci = data->math.max_i + y * step[1];
	x = 0;
	while (x < data->win_width)
	{
		it = data->fractal.iterate(data, data->math.min_r + x * step[0], ci);
		if (it >= data->fractal.max_iterations)
			row[x] = 0;
		else
			row[x] = make_color(data, it);
		x++;
	}
}

int
	render_set(t_data *data)
{
	unsigned int	*pixel;
	double			step[2];
	int				y;

	pixel = (unsigned int *)data->image.addr;
	step[0] = (data->math.max_r - data->math.min_r) / (double)data->win_width;
	if (data->set == BURNING_SHIP)
		step[1] = (data->math.max_i - data->math.min_i)
			/ (double)data->win_height;
	else
		step[1] = (data->math.min_i - data->math.max_i)
			/ (double)data->win_height;
	y = 0;
	while (y < data->win_height)
	{
		render_row(data, pixel + y * (data->image.size_line / 4), y, step);
		y++;
	}
	return (TRUE);
}
