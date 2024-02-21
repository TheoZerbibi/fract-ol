/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:18:40 by mjacquet          #+#    #+#             */
/*   Updated: 2024/02/21 09:44:04 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <X11/Xlib.h>
# include <X11/extensions/XShm.h>
# include <sys/wait.h>
# include "define.h"

typedef struct s_mlx	t_mlx;
typedef struct s_data	t_data;
typedef struct s_img	t_img;
typedef struct s_color	t_color;

struct s_img
{
	void	*image;
	char	*addr;
	int		size_line;
	int		bpp;
	int		endian;
	int		width;
	int		height;
};

struct s_mlx
{
	void	*mlx;
	void	*win;
};

struct s_color
{
	int		r;
	int		g;
	int		b;
	char	*color;
};
struct s_data
{
	int			win_width;
	int			win_height;
	t_mlx		mlx;
	t_img		image;
};

#endif
