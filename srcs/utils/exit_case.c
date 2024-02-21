/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 06:45:25 by thzeribi          #+#    #+#             */
/*   Updated: 2024/02/21 12:52:34 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
** @name exit_init();
** @brief Call when initialisation failed.
**
** @param t_data *data
**/
void
	exit_init(t_data *data)
{
	ft_putstr("\e[1;31mError\nA problem occurred during initialisation !\e[0m\n");
	_end_mlx(data, 1);
}

/**
** @name exit_usage();
** @brief Call when usage is incorrect, exit after print error.
**/
void
	exit_usage(void)
{
	ft_putstr("\n\t\t\t\e[1;31m! [INVALID USAGE] !\e[0m\n");
	ft_putstr("\n\t\e[0;36mCorrect usage is	: ");
	ft_putstr("\e[0;92m./fractol <FractalSet>\e[0m\n");
	ft_putstr("\t\e[0;36mExemple\t\t\t: ");
	ft_putstr("\e[0;92m./fractol Mandelbrot\e[0m\n");
	ft_putstr("\t\e[0;36mFractol Set\t\t: ");
	ft_putstr("\e[0;92m[Mandelbrot, Julia, Buddhabrot, Burning_ship]\e[0m\n");
	exit(1);
}
