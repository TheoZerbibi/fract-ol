/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 21:13:32 by thzeribi          #+#    #+#             */
/*   Updated: 2024/02/21 09:41:33 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void
	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->data + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void
	reset_img(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < H)
	{
		x = 0;
		while (x < W)
		{
			my_mlx_pixel_put(&(data->image), x, y, 0x000000);
			x++;
		}
		y++;
	}
}
