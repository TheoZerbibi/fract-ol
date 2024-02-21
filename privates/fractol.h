/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:01:30 by mjacquet          #+#    #+#             */
/*   Updated: 2024/02/21 09:50:11 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "mlx.h"
# include "struct.h"
# include "libft.h"
# include "keycodes.h"
# include "define.h"
# include "error.h"

# ifndef BONUS
#  define BONUS 0
# endif

# define TITLE "Fractol"

int		_init_img(t_data *data);
int		_init_mlx(t_data *data);
int		_end_mlx(t_data *data, int err);

void	setup_hook(t_data *data);
int		keypress(int keycode, t_data *datafractol);
int		zoom(int keycode, t_data *data);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);

void	exit_init(t_data *data);

#endif
