/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 05:37:57 by thzeribi          #+#    #+#             */
/*   Updated: 2024/02/21 09:41:22 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	return (keycode);
}
