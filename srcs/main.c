/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:41:11 by thzeribi          #+#    #+#             */
/*   Updated: 2025/01/05 20:18:02 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#ifdef BONUS
# include "bonus.h"
#endif

/**
** @name lower_set_name(); [Static Function]
** @brief Call by main function, this function lower the set name
** to avoid case sensitive.
**
** @param char *set 
**/
static void lower_set_name(char *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		set[i] = ft_tolower(set[i]);
		i++;
	}
}

/**
** @name draw_fractol();
** @brief Call by main function, this function call and draw the fractal set
** compared to fractol->set defined earlier.
**
** @param t_fractol *fractol
**/
int draw_fractol(t_data *data)
{
    if (data->show_usage)
        usage_background(data, 0x000222222);
    mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->image.image, 0, 0);
    if (data->show_usage)
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
#ifdef BONUS
static int
	init_fractol_set(char *set, t_data *data)
{
	lower_set_name(set);
	if (ft_strcmp(set, "mandelbrot") == 0
		|| (ft_strlen(set) == 1 && set[0] == 'm'))
	{
		data->fractal.draw = &mandelbrot_bonus;
		data->fractal.iterate = &is_mandelbrot_smooth;
		init_mandelbrot(data);
		data->set = MANDELBROT;
	}
	else if (ft_strcmp(set, "julia") == 0
		|| (ft_strlen(set) == 1 && set[0] == 'j'))
	{
		// data->fractal.iterate = &is_julia_esmooth;
		// data->fractal.draw = &julia_bonus;
		// init_julia(data);
		data->set = JULIA;
	}
	else if (ft_strcmp(set, "buddhabrot") == 0
		|| (ft_strlen(set) == 1 && set[0] == 'b'))
	{
		// data->fractal.iterate = &is_buddhabrot_smooth;
		// data->fractal.draw = &buddhabrot_bonus;
		// init_buddhabrot(data);
		data->set = BUDDHABROT;
	}
	else if (ft_strcmp(set, "burning_ship") == 0
		|| (ft_strlen(set) == 2 && set[0] == 'b' && set[1] == 's'))
	{
		data->fractal.draw = &burningship_bonus;
		data->fractal.iterate = &is_burningship_smooth;
		init_burning_ship(data);
		data->set = BURNING_SHIP;
	}
	else
		return (-1);
	return (TRUE);
}
#else
static int
	init_fractol_set(char *set, t_data *data)
{
	lower_set_name(set);
	if (ft_strcmp(set, "mandelbrot") == 0
		|| (ft_strlen(set) == 1 && set[0] == 'm'))
	{
		data->fractal.draw = &mandelbrot;
		data->fractal.iterate = &is_mandelbrot_smooth;
		init_mandelbrot(data);
		data->set = MANDELBROT;
	}
	else if (ft_strcmp(set, "julia") == 0
		|| (ft_strlen(set) == 1 && set[0] == 'j'))
	{
		data->fractal.iterate = &is_julia_smooth;
		data->fractal.draw = &julia;
		init_julia(data);
		data->set = JULIA;
	}
	else if (ft_strcmp(set, "buddhabrot") == 0
		|| (ft_strlen(set) == 1 && set[0] == 'b'))
	{
		data->fractal.iterate = &is_buddhabrot_smooth;
		data->fractal.draw = &buddhabrot;
		init_buddhabrot(data);
		data->set = BUDDHABROT;
	}
	else if (ft_strcmp(set, "burning_ship") == 0
		|| (ft_strlen(set) == 2 && set[0] == 'b' && set[1] == 's'))
	{
		data->fractal.draw = &burning_ship;
		data->fractal.iterate = &is_burningship_smooth;
		init_burning_ship(data);
		data->set = BURNING_SHIP;
	}
	else
		return (-1);
	return (TRUE);
}
#endif

/**
** @name main();
** @brief This function is the main function.
**
** @param int argc
** @param char *argv[]
**/

int
	main(int argc, char *argv[])
{
	t_data  data;
#ifdef BONUS
	printf("BONUS ENABLED\n");
#endif
	data = (t_data){.show_usage = TRUE};
	if (!_init_mlx(&data) || !_init_img(&data))
		exit_init(&data);
	if (argc != 2 || init_fractol_set(argv[1], &data) == -1)
		exit_usage(&data);
	mlx_loop_hook(data.mlx.mlx, &draw_fractol, &data);
	mlx_loop(data.mlx.mlx);
	_end_mlx(&data, 0);
	return (0);
}
