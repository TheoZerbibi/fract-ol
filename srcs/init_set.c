/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:14:16 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/20 15:00:00 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void
	lower_set_name(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = ft_tolower(src[i]);
		i++;
	}
	dst[i] = '\0';
}

static int
	init_set_extra(char *set, t_data *data)
{
	if (ft_strcmp(set, "julia") == 0 || (ft_strlen(set) == 1 && set[0] == 'j'))
	{
		data->fractal.draw = &julia;
		init_julia(data);
		data->set = JULIA;
	}
	else if (ft_strcmp(set, "buddhabrot") == 0
		|| (ft_strlen(set) == 2 && set[0] == 'b' && set[1] == 'b'))
	{
		data->fractal.draw = &buddhabrot;
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
		data->fractal.draw = &burning_ship;
		init_burning_ship(data);
		data->set = BURNING_SHIP;
	}
	else if (ft_strcmp(set, "phoenix") == 0
		|| (ft_strlen(set) == 1 && set[0] == 'p'))
	{
		data->fractal.draw = &phoenix;
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
	char	buf[32];

	lower_set_name(buf, set);
	if (ft_strcmp(buf, "mandelbrot") == 0
		|| (ft_strlen(buf) == 1 && buf[0] == 'm'))
	{
		data->fractal.draw = &mandelbrot;
		init_mandelbrot(data);
		data->set = MANDELBROT;
	}
	else
		return (init_set_second(buf, data));
	return (TRUE);
}
