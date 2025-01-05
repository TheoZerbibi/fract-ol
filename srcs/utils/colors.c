/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:05:36 by thzeribi          #+#    #+#             */
/*   Updated: 2025/01/05 02:45:26 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_color palette1[] = {
	{66, 30, 15},    // Brun foncé
	{25, 7, 26},     // Violet foncé
	{9, 1, 47},      // Bleu marine
	{4, 4, 73},      // Bleu profond
	{0, 7, 100},     // Bleu intense
	{12, 44, 138},   // Bleu moyen
	{24, 82, 177},   // Bleu clair
	{57, 125, 209},  // Bleu lumineux
	{134, 181, 229}, // Bleu pâle
	{211, 236, 248}, // Bleu très pâle
	{241, 233, 191}, // Jaune pâle
	{248, 201, 95},  // Orange clair
	{255, 170, 0},   // Orange
	{204, 128, 0},   // Orange foncé
	{153, 87, 0},    // Brun clair
	{106, 52, 3}     // Brun
};

t_color palette2[] = {
	{148, 0, 211},    // Violet
	{75, 0, 130},     // Indigo
	{0, 0, 255},      // Bleu
	{0, 255, 0},      // Vert
	{255, 255, 0},    // Jaune
	{255, 127, 0},    // Orange
	{255, 0, 0}       // Rouge
};

t_color palette3[] = {
	{7, 7, 7},
	{31, 7, 7},
	{47, 15, 7},
	{71, 15, 7},
	{87, 23, 7},
	{103, 31, 7},
	{119, 31, 7},
	{143, 39, 7},
	{159, 47, 7},
	{175, 63, 7},
	{191, 71, 7},
	{199, 71, 7},
	{223, 79, 7},
	{223, 87, 7},
	{223, 87, 7},
	{215, 95, 7},
	{215, 95, 7},
	{215, 103, 15},
	{207, 111, 15},
	{207, 119, 15},
	{207, 127, 15},
	{207, 135, 23},
	{199, 135, 23},
	{199, 143, 23},
	{199, 151, 31},
	{191, 159, 31},
	{191, 159, 31},
	{191, 167, 39},
	{191, 167, 39},
	{191, 175, 47},
	{183, 175, 47},
	{183, 183, 47},
	{183, 183, 55},
	{207, 207, 111},
	{223, 223, 159},
	{239, 239, 199},
	{255, 255, 255}
};
int palette1_size = sizeof(palette1) / sizeof(t_color);
int palette2_size = sizeof(palette2) / sizeof(t_color);
int palette3_size = sizeof(palette3) / sizeof(t_color);

double lerp(double a, double b, double t) {
	return a + t * (b - a);
}

t_color interpolate(t_color c1, t_color c2, double t) {
	t_color result;
	result.r = (int)lerp(c1.r, c2.r, t);
	result.g = (int)lerp(c1.g, c2.g, t);
	result.b = (int)lerp(c1.b, c2.b, t);
	return result;
}

void change_color_shift(t_data *data) {
	data->fractal.color_shift++;
	if (data->fractal.color_shift > NUM_PALETTES)
		data->fractal.color_shift = 1;
}

int make_color(t_data *data, double iteration) {
	t_color *palettes[NUM_PALETTES] = { palette1, palette2, palette3 };
	int palette_sizes[NUM_PALETTES] = { sizeof(palette1) / sizeof(t_color), sizeof(palette2) / sizeof(t_color), sizeof(palette3) / sizeof(t_color) };
	int current_palette = (data->fractal.color_shift - 1) % NUM_PALETTES;
	t_color *palette = palettes[current_palette];
	int palette_size = palette_sizes[current_palette];
	double t = iteration / MAX_ITER;
	if (t > 1.0)
		t = 1.0;
	double scaled_t = t * (palette_size - 1);
	int index = (int)scaled_t;
	double frac = scaled_t - index;
	
	if (index >= palette_size - 1) {
		index = palette_size - 2;
		frac = 1.0;
	}
	t_color color = interpolate(palette[index], palette[index + 1], frac);
	return create_trgb(0, clamp_color(color.r), clamp_color(color.g), clamp_color(color.b));
}

int
	create_trgb(int t, int r, int g, int b) {
	return (t << 24 | r << 16 | g << 8 | b);
}

int clamp_color(int c) {
	if (c < 0)
		return 0;
	else if (c > 255)
		return 255;
	return c;
}

double
	smooth_iteration(int iteration, double zr, double zi) {
    if (iteration >= MAX_ITER)
        return (double)iteration;
    double z_squared = zr * zr + zi * zi;
    return iteration + 1 - log(log(sqrt(z_squared))) / log(2);
}
