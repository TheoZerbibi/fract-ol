/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:41:11 by thzeribi          #+#    #+#             */
/*   Updated: 2025/01/05 16:15:20 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#ifdef BONUS
# include "bonus.h"
#endif

static int
	parse_julia_args(int argc, char **argv, t_data *data)
{
	if (argc == 4)
	{
		data->fractal.julia_shiftx = ft_atof(argv[2]);
		data->fractal.julia_shifty = ft_atof(argv[3]);
		data->fractal.julia_locked = 1;
	}
	else
		data->fractal.julia_locked = 0;
	return (TRUE);
}

int
	draw_fractol(t_data *data)
{
	update_fps(data);
	data->fractal.draw(data);
	if (data->show_usage)
		usage_background(data, 0x000222222);
	if (data->perf.show_debug)
		debug_background(data, 0x00222222);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->image.image, 0,
		0);
	if (data->show_usage)
		draw_usage(data, 0xEEEEEE);
	draw_debug_overlay(data, 0x00EEEEEE);
	return (0);
}

int
	main(int argc, char *argv[])
{
	t_data	data;

	data = (t_data){.show_usage = TRUE};
	if (!_init_mlx(&data) || !_init_img(&data))
		exit_init(&data);
	if (argc < 2 || argc > 4 || init_fractol_set(argv[1], &data) == -1)
		exit_usage(&data);
	if (data.set == JULIA)
		parse_julia_args(argc, argv, &data);
	mlx_loop_hook(data.mlx.mlx, &draw_fractol, &data);
	mlx_loop(data.mlx.mlx);
	_end_mlx(&data, 0);
	return (0);
}
