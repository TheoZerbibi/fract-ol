/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:41:11 by thzeribi          #+#    #+#             */
/*   Updated: 2024/02/21 12:52:20 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
** @name draw_fractol();
** @brief Call by main function, this function call and draw the fractal set
** compared to fractol->set defined earlier.
**
** @param t_fractol *fractol
**/
int
	draw_fractol(t_data *data)
{
	if (data->set == MANDELBROT)
		mandelbrot(data);
	usage_background(data, 0x000222222);
	mlx_put_image_to_window(data->mlx.mlx, \
		data->mlx.win, data->image.image, 0, 0);
	draw_usage(data, 0xEEEEEE);
	return (0);
}

/**
** @name init_fractol_set(); [Static Function]
** @brief Call by main function, this function init the fractol set
** among a predefined enum class call e_fractal_set{}.
**
** @param char *set
** @param t_data *data
** @return TRUE [1]
** @return FALSE [0]
**/
static int
	init_fractol_set(char *set, t_data *data)
{
	if (!ft_strcmp(set, "Mandelbrot") || !ft_strcmp(set, "M"))
		data->set = MANDELBROT;
	else if (!ft_strcmp(set, "Julia") || !ft_strcmp(set, "J"))
		data->set = JULIA;
	else if (!ft_strcmp(set, "Buddhabrot") || !ft_strcmp(set, "B"))
		data->set = BUDDHABROT;
	else if (!ft_strcmp(set, "Burning_ship") || !ft_strcmp(set, "BS"))
		data->set = BURNING_SHIP;
	else
		return (FALSE);
	return (TRUE);
}

/**
** @name main();
** @brief This function is the main function.
**
** @param int argc
** @param char *argv[]
**/

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2 || !init_fractol_set(argv[1], &data))
		exit_usage();
	data = (t_data){0};
	if (!_init_mlx(&data) || !_init_img(&data))
		exit_init(&data);
	if (!BONUS)
		mlx_loop_hook(data.mlx.mlx, &draw_fractol, &data);
	draw_fractol(&data);
	mlx_loop(data.mlx.mlx);
	_end_mlx(&data, 0);
	return (0);
}
