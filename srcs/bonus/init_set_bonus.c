/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_set_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 15:00:00 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/20 15:00:00 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

static void
	lower_set_name(char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		set[i] = ft_tolower(set[i]);
		i++;
	}
}

static int
	init_set_extra(char *set, t_data *data)
{
	if (ft_strcmp(set, "julia") == 0 || (ft_strlen(set) == 1 && set[0] == 'j'))
	{
		data->fractal.draw = &julia_bonus;
		init_julia(data);
		data->set = JULIA;
	}
	else if (ft_strcmp(set, "buddhabrot") == 0
		|| (ft_strlen(set) == 2 && set[0] == 'b' && set[1] == 'b'))
	{
		data->fractal.draw = &buddhabrot_bonus;
		init_buddhabrot(data);
		data->set = BUDDHABROT;
	}
	else
		return (-1);
	return (TRUE);
}

static int
	init_set_second(char *set, t_data *data)
{
	if (ft_strcmp(set, "burning_ship") == 0
		|| (ft_strlen(set) == 2 && set[0] == 'b' && set[1] == 's'))
	{
		data->fractal.draw = &burningship_bonus;
		init_burning_ship(data);
		data->set = BURNING_SHIP;
	}
	else if (ft_strcmp(set, "phoenix") == 0
		|| (ft_strlen(set) == 1 && set[0] == 'p'))
	{
		data->fractal.draw = &phoenix_bonus;
		init_phoenix(data);
		data->set = PHOENIX;
	}
	else
		return (init_set_extra(set, data));
	return (TRUE);
}

int
	init_fractol_set(char *set, t_data *data)
{
	int	ret;

	ret = write(1, "Bonus mode enabled\n", 19);
	if (ret < 0)
		return (-1);
	lower_set_name(set);
	if (ft_strcmp(set, "mandelbrot") == 0
		|| (ft_strlen(set) == 1 && set[0] == 'm'))
	{
		data->fractal.draw = &mandelbrot_bonus;
		init_mandelbrot(data);
		data->set = MANDELBROT;
	}
	else
		return (init_set_second(set, data));
	return (TRUE);
}
