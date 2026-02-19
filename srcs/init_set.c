/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:14:16 by thzeribi          #+#    #+#             */
/*   Updated: 2025/01/05 16:16:27 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#ifdef BONUS
# include "bonus.h"
#endif

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
	init_set_extra(char *set, t_data *data) {
	if (ft_strcmp(set, "julia") == 0 || (ft_strlen(set) == 1 && set[0] == 'j'))
	{
#ifdef BONUS
		data->fractal.draw = &julia_bonus;
#else
		data->fractal.draw = &julia;
#endif
		init_julia(data);
		data->set = JULIA;
	}
	else if (ft_strcmp(set, "buddhabrot") == 0
		|| (ft_strlen(set) == 2 && set[0] == 'b' && set[1] == 'b'))
	{
#ifdef BONUS
		data->fractal.draw = &buddhabrot_bonus;
#else
		data->fractal.draw = &buddhabrot;
#endif
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
#ifdef BONUS
		data->fractal.draw = &burningship_bonus;
#else
		data->fractal.draw = &burning_ship;
#endif
		init_burning_ship(data);
		data->set = BURNING_SHIP;
	}
	else if (ft_strcmp(set, "phoenix") == 0
		|| (ft_strlen(set) == 1 && set[0] == 'p'))
	{
#ifdef BONUS
		data->fractal.draw = &phoenix_bonus;
#else
		data->fractal.draw = &phoenix;
#endif
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
	lower_set_name(set);
	if (ft_strcmp(set, "mandelbrot") == 0
		|| (ft_strlen(set) == 1 && set[0] == 'm'))
	{
#ifdef BONUS
		data->fractal.draw = &mandelbrot_bonus;
#else
		data->fractal.draw = &mandelbrot;
#endif
		init_mandelbrot(data);
		data->set = MANDELBROT;
	}
	else
		return (init_set_second(set, data));
	return (TRUE);
}
