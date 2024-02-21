/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:41:11 by thzeribi          #+#    #+#             */
/*   Updated: 2024/02/21 10:09:12 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int
	get_random_color(void)
{
	int		color;
	int		r;
	int		g;
	int		b;

	color = 0;
	r = rand() % 255;
	g = rand() % 255;
	b = rand() % 255;
	color = r << 16 | g << 8 | b;
	return (color);
}

int
	game_loop(t_data *data)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < data->win_height)
	{
		while (x < data->win_width)
		{
			mlx_pixel_put(data->mlx.mlx, data->mlx.win, x, y, \
				get_random_color());
			x++;
		}
		x = 0;
		y++;
	}
	return (TRUE);
}

int	main(void)
{
	t_data	data;

	data = (t_data){0};
	if (!_init_mlx(&data) || !_init_img(&data))
		exit_init(&data);
	if (BONUS)
		printf("\e[1;33mBonus\e[0m\n");
	mlx_loop_hook(data.mlx.mlx, game_loop, &data);
	mlx_loop(data.mlx.mlx);
	_end_mlx(&data, 0);
	return (0);
}
