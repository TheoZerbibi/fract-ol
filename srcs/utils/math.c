/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:30:19 by thzeribi          #+#    #+#             */
/*   Updated: 2025/01/05 17:00:55 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double
	calculate_scale_ratio(t_data *data)
{
	double	initial_width;
	double	current_width;

	initial_width = data->math.initial_max_r - data->math.initial_min_r;
	current_width = data->math.max_r - data->math.min_r;
	return (initial_width / current_width);
}

void
	adjust_max_iterations(t_data *data)
{
	double	scale_ratio;
	double	base_iterations;

	scale_ratio = calculate_scale_ratio(data);
	base_iterations = (double)MAX_ITER;
	data->fractal.max_iterations = (int)(base_iterations * scale_ratio);
	if (data->fractal.max_iterations > 10000)
		data->fractal.max_iterations = 10000;
	if (data->fractal.max_iterations < 100)
		data->fractal.max_iterations = 100;
}

void
	initialize_math(t_data *data)
{
	data->math.initial_min_r = data->math.min_r;
	data->math.initial_max_r = data->math.max_r;
	data->math.initial_min_i = data->math.min_i;
	data->math.initial_max_i = data->math.max_i;
}
