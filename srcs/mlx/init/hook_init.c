/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 05:35:19 by thzeribi          #+#    #+#             */
/*   Updated: 2024/02/21 12:45:45 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
** @name setup_hook();
** @brief Call by _init_mlx() function. This function init all hook event.
**
** @param t_data *data
**/
void
	setup_hook(t_data *data)
{
	mlx_hook(data->mlx.win, KeyPress, KeyPressMask, &keypress, data);
	mlx_hook(data->mlx.win, 33, (1L << 17), _end_mlx, data);
}
