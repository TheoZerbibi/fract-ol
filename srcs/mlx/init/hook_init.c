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

static int
	close_window(t_data *data)
{
	end_mlx(data, 0);
	return (0);
}

/**
 * @brief    Register X11 event hooks with MiniLibX.
 *
 * @param    data   Application state.
 * @note     Uses X11 event masks: KeyPressMask for keyboard, ButtonPressMask
 *           for mouse clicks/scrolls, PointerMotionMask for mouse tracking,
 *           and StructureNotifyMask for window close events (ClientMessage).
 */
void
	setup_hook(t_data *data)
{
	mlx_hook(data->mlx.win, KeyPress, KeyPressMask, &keypress, data);
	mlx_hook(data->mlx.win, ButtonPress, ButtonPressMask, &mouse, data);
	mlx_hook(data->mlx.win, MotionNotify, PointerMotionMask,
		&julia_mouse_move, data);
	mlx_hook(data->mlx.win, ClientMessage, StructureNotifyMask,
		close_window, data);
}
