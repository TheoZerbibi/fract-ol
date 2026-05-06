/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simd_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:00:00 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/20 14:00:00 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

void
	put_pixel_simd(t_thread_data *info, int x, int y, long long it)
{
	unsigned int	*row;

	row = (unsigned int *)(info->data->image.addr
			+ y * info->data->image.size_line);
	if (it >= info->data->fractal.max_iterations)
		row[x] = 0;
	else
		row[x] = make_color(info->data, (double)it);
}

void
	render_thread_row_remainder(t_thread_data *info,
	int y, double ci, int x)
{
	double			cr;
	double			it;
	unsigned int	*row;

	row = (unsigned int *)(info->data->image.addr
			+ y * info->data->image.size_line);
	while (x < info->data->win_width)
	{
		cr = info->data->math.min_r + x * info->step_r;
		it = info->data->fractal.iterate(info->data, cr, ci);
		if (it >= info->data->fractal.max_iterations)
			row[x] = 0;
		else
			row[x] = make_color(info->data, it);
		x++;
	}
}
