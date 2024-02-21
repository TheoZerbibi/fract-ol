/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 05:33:14 by thzeribi          #+#    #+#             */
/*   Updated: 2024/02/21 12:19:42 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
** @name init_img()
** @brief Call by main function, this function init the img used
** to render project set later.
**
** @param t_data *data
** @return TRUE [1]
** @return FALSE [0]
**/
int
	_init_img(t_data *data)
{
	data->image.image = mlx_new_image(data->mlx.mlx, data->win_width,
			data->win_height);
	if (!data->image.image)
		return (FALSE);
	data->image.addr = mlx_get_data_addr(data->image.image, &data->image.bpp,
			&data->image.size_line, &data->image.endian);
	if (!data->image.addr)
		return (FALSE);
	data->image.width = data->win_width;
	data->image.height = data->win_height;
	return (TRUE);
}

/**
** @name _init_mlx()
** @brief Call by main function, this function init mlx lib
** and all dependencies
**
** @param t_data *data
** @return TRUE [1]
** @return FALSE [0]
**/
int
	_init_mlx(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		return (FALSE);
	mlx_get_screen_size(data->mlx.mlx, &data->win_width, &data->win_height);
	data->mlx.win = mlx_new_window(data->mlx.mlx, data->win_width,
			data->win_height, TITLE);
	if (!data->mlx.win)
		return (FALSE);
	setup_hook(data);
	return (TRUE);
}
