/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddhabrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:14:16 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/19 11:12:42 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void
	find_hist_max(t_data *data)
{
	unsigned int	mx;
	int				total;
	int				i;

	total = data->win_width * data->win_height;
	mx = 0;
	i = 0;
	while (i < total)
	{
		if (data->histogram[i] > mx)
			mx = data->histogram[i];
		i++;
	}
	data->hist_max = mx;
}

static void
	clear_histogram(t_data *data)
{
	int	total;

	total = data->win_width * data->win_height;
	while (--total >= 0)
		data->histogram[total] = 0;
}

static void
	render_histogram(t_data *data)
{
	unsigned int	*px;
	double			ratio;
	int				total;
	int				i;

	px = (unsigned int *)data->image.addr;
	total = data->win_width * data->win_height;
	i = 0;
	while (i < total)
	{
		if (data->hist_max > 0)
			ratio = (double)data->histogram[i] / (double)data->hist_max;
		else
			ratio = 0.0;
		px[i] = make_space_color(ratio);
		i++;
	}
}

int
	buddhabrot(t_data *data)
{
	if (!data->histogram)
		return (FALSE);
	clear_histogram(data);
	sample_buddhabrot(data, BUDDHA_SAMPLES);
	find_hist_max(data);
	render_histogram(data);
	return (TRUE);
}
