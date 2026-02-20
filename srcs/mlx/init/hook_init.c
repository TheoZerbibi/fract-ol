/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 05:35:19 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/19 10:26:32 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void
	setup_hook(t_data *data)
{
	mlx_hook(data->mlx.win, KeyPress, KeyPressMask, &keypress, data);
	mlx_hook(data->mlx.win, ButtonPress, ButtonPressMask, &mouse, data);
	mlx_hook(data->mlx.win, 6, (1L << 6), &julia_mouse_move, data);
	mlx_hook(data->mlx.win, 33, (1L << 17), _end_mlx, data);
}
