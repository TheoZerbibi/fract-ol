/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 05:37:57 by thzeribi          #+#    #+#             */
/*   Updated: 2024/02/22 07:54:01 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void
	move(t_data	*data, char direction)
{
	t_math *math = &data->math;
	double width = data->math.max_r - data->math.min_r;
	double height = data->math.max_i - data->math.min_i;

	math->center_r = math->min_r - math->max_r;
	math->center_i = math->min_i - math->max_i;
	if (direction == 'U')
	{
		math->min_i += 0.1 * height;
		math->max_i += 0.1 * height;
	}
	if (direction == 'D')
	{
		math->min_i -= 0.1 * height;
		math->max_i -= 0.1 * height;
	}
	if (direction == 'R')
	{
		math->min_r += 0.1 * width;
		math->max_r += 0.1 * width;
	}
	if (direction == 'L')
	{
		math->min_r -= 0.1 * width;
		math->max_r -= 0.1 * width;
	}
	return ;
}

/**
** @name keypress();
** @brief Call when key is pressed. This function is init
** by mlx_key_hook() from MLX Lib in setup_hook() function.
**
** @param int keycode
** @param t_data *data
** @return keycode
**/
int
	keypress(int keycode, t_data *data)
{
	if (keycode == K_ESC)
		_end_mlx(data, 0);
	if (keycode == K_SPACE)
		data->show_usage = !data->show_usage;
	if (keycode == K_SHIFT)
		change_color_shift(data);
	if (keycode == K_W || keycode == K_UP)
		move(data, 'U');
	if (keycode == K_S || keycode == K_DOWN)
		move(data, 'D');
	if (keycode == K_A || keycode == K_LEFT)
		move(data, 'L');
	if (keycode == K_D || keycode == K_RIGHT)
		move(data, 'R');
	return (keycode);
}
