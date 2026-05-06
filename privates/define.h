/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:57:39 by thzeribi          #+#    #+#             */
/*   Updated: 2025/01/05 07:10:01 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# include <X11/keysym.h>

enum e_fractal_set
{
	MANDELBROT,
	JULIA,
	BUDDHABROT,
	BURNING_SHIP,
	PHOENIX
};

# ifndef MAX_ITER
#  ifdef BONUS
#   define MAX_ITER 2000
#  else
#   define MAX_ITER 150
#  endif
# endif

# define TITLE "Fractol"
# define INITIAL_ZOOM 4.0
# define NUM_PALETTES 3
# define BUDDHA_SAMPLES 500000
# define BUDDHA_ITER 200
# define BUDDHA_RAND_RES 100000
# define BUDDHA_MIN_R -2.0
# define BUDDHA_MAX_R 1.0
# define BUDDHA_MIN_I -1.5
# define BUDDHA_MAX_I 1.5
# define BUDDHA_RANGE_R 3.0
# define BUDDHA_RANGE_I 3.0

# define BLACK		"\e[30m"
# define RED		"\e[31m"
# define GREEN		"\e[32m"
# define YELLOW		"\e[33m"
# define BLUE		"\e[34m"
# define MAGENTA	"\e[35m"
# define CYAN		"\e[36m"
# define WHITE		"\e[37m"
# define RESET		"\e[0m"

# define TRUE 1
# define FALSE 0

# define PI 3.14159265358979323846264338327950288419716939937510582
# define DR 0.0174533

# define RGB_LIGHT_GREY	0x00888888
# define RGB_RED		0x00FF0000
# define RGB_RED2		0x00FF5555
# define RGB_GREEN		0x0000FF00
# define RGB_GREEN2		0x0066AA22
# define RGB_BLUE		0x000000FF
# define RGB_WHITE		0x00FFFFFF
# define RGB_YELLOW		0x00FFFF00
# define RGB_BLACK		0x00000000
# define RGB_BROWN5		0x0042302A
# define RGB_BROWN4		0x00341107
# define RGB_BROWN3		0x00612711
# define RGB_BROWN2		0x00D18A5B
# define RGB_BROWN		0x00885500
# define RGB_SKY_BLUE	0x0065BCEB
# define RGB_TR			0xFF

# define RGB_OVERLAY_BG		0x00222222
# define RGB_OVERLAY_TEXT	0x00EEEEEE

# define MOUSE_SCROLL_UP	4
# define MOUSE_SCROLL_DOWN	5

# define ZOOM_IN		0.9
# define ZOOM_OUT		1.1
# define MAX_ZOOM_MULT	1.5
# define MIN_ZOOM_STEP	1e-13

# define MOVE_STEP		0.1

# define ITER_BASE_DIV	6
# define ITER_FLOOR		50
# define LOG_BASE		10.0

# define JULIA_ARGC		4
# define JULIA_MIN		-2.0
# define JULIA_RANGE	4.0

#endif
