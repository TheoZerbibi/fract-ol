/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:18:40 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/19 11:59:16 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <X11/Xlib.h>
# include <X11/extensions/XShm.h>
# include <sys/wait.h>
# include <sys/time.h>
# include "define.h"

typedef struct s_mlx		t_mlx;
typedef struct s_data		t_data;
typedef struct s_img		t_img;
typedef struct s_fractal	t_fractal;
typedef struct s_math		t_math;
typedef struct s_perf		t_perf;
typedef union u_bit_hack	t_bit_hack;
typedef struct s_color		t_color;

/**
 * @brief    RGB color triplet.
 */
struct s_color
{
	int	r; /**< Red channel (0-255). */
	int	g; /**< Green channel (0-255). */
	int	b; /**< Blue channel (0-255). */
};

/**
 * @brief    IEEE 754 double-precision bit manipulation union.
 *
 * Used by fast_log2() to extract the exponent and mantissa of a double
 * without calling log(), enabling a branchless approximate log2.
 */
union u_bit_hack
{
	double		d; /**< Double-precision floating-point view. */
	long long	i; /**< 64-bit integer view for bit-level access. */
};

/**
 * @brief    Performance metrics and debug display state.
 */
struct s_perf
{
	struct timeval	last_time; /**< Timestamp of the previous frame. */
	double			fps; /**< Current frames per second. */
	int				show_debug; /**< Debug overlay visibility toggle. */
};

/**
 * @brief    MiniLibX image buffer descriptor.
 *
 * Wraps the off-screen pixel buffer used for direct memory rendering.
 * Pixels are written to addr and flushed to the window in a single call.
 */
struct s_img
{
	void	*image; /**< Opaque MiniLibX image pointer. */
	char	*addr; /**< Raw pixel buffer (BGRA byte order). */
	int		size_line; /**< Number of bytes per scanline. */
	int		bpp; /**< Bits per pixel (typically 32). */
	int		endian; /**< Byte order (0 = little-endian, 1 = big-endian). */
	int		width; /**< Image width in pixels. */
	int		height; /**< Image height in pixels. */
};

struct s_mlx
{
	void	*mlx;
	void	*win;
};

/**
 * @brief    Complex plane viewport boundaries.
 *
 * Defines the rectangular region of the complex plane currently visible.
 * Pixel (px, py) maps to complex number:
 *   re = min_r + px * (max_r - min_r) / win_width
 *   im = max_i - py * (max_i - min_i) / win_height
 */
struct s_math
{
	double			min_r; /**< Left boundary (minimum real value). */
	double			max_r; /**< Right boundary (maximum real value). */
	double			min_i; /**< Bottom boundary (minimum imaginary value). */
	double			max_i; /**< Top boundary (maximum imaginary value). */
	unsigned int	count; /**< Render pass counter. */
	double			center_i; /**< Cached center imaginary coordinate. */
	double			center_r; /**< Cached center real coordinate. */
};

/**
 * @brief    Fractal rendering configuration and function pointers.
 */
struct s_fractal
{
	int		color_shift; /**< Active palette index. */
	int		resolution_shift; /**< Pixel skip factor for low-res preview. */
	double	julia_shiftx; /**< Julia parameter c real part. */
	double	julia_shifty; /**< Julia parameter c imaginary part. */
	int		julia_locked; /**< If Julia c parameter is fixed or mouse-track. */
	double	phoenix_p; /**< Phoenix fractal perturbation coefficient. */
	int		max_iterations; /**< Maximum escape-time iterations. */
	int		(*draw)(struct s_data *data); /**< Pointer set's draw routine. */
	double	(*iterate)(struct s_data *, double, double); /**< pointer to draw.*/
};

/**
 * @brief    Root application state.
 *
 * Contains all program state: window dimensions, MiniLibX handles,
 * fractal configuration, viewport math, and rendering buffers.
 */
struct s_data
{
	int					win_width; /**< Window width in pixels. */
	int					win_height; /**< Window height in pixels. */
	int					show_usage; /**< Usage overlay visibility toggle. */
	int					dirty; /**< Render invalidation flag. */
	enum e_fractal_set	set; /**< Active fractal set enum value. */
	t_mlx				mlx; /**< MiniLibX connection and window handles. */
	t_img				image; /**< Off-screen pixel buffer. */
	t_fractal			fractal; /**< Fractal type config and func pointers. */
	t_math				math; /**< Complex plane viewport boundaries. */
	t_color				color; /**< Scratch color value. */
	t_perf				perf; /**< FPS counter and debug state. */
	unsigned int		*histogram; /**< Buddhabrot hit-count buffer. */
	unsigned int		hist_max; /**< Maximum histog bin val for normaliza. */
};

#endif
