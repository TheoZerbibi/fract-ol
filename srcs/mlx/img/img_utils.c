/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 21:13:32 by thzeribi          #+#    #+#             */
/*   Updated: 2025/01/05 04:22:43 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void
    my_mlx_pixel_put(t_img *image, int x, int y, int color)
{
    char    *dst;

    if (x < 0 || x >= image->width || y < 0 || y >= image->height)
        return;

    dst = image->addr + (y * image->size_line + x * (image->bpp / 8));
    *(unsigned int*)dst = color;
}

void
	reset_img(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->win_height)
	{
		x = 0;
		while (x < data->win_width)
		{
			my_mlx_pixel_put(&(data->image), x, y, 0x000000);
			x++;
		}
		y++;
	}
}
