/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 06:45:25 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/19 10:53:30 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void
	exit_init(t_data *data)
{
	ft_putstr("\e[1;31mError\n\e[0m\n");
	ft_putstr("\e[1;31mA problem occurred during initialisation!\e[0m\n");
	end_mlx(data, 1);
}

static void
	print_usage_sets(void)
{
	ft_putstr("\t\e[0;36mJulia usage\t\t: ");
	ft_putstr("\e[0;92m./fractol Julia <cr> <ci>\e[0m\n");
	ft_putstr("\t\e[0;36mExemple\t\t\t: ");
	ft_putstr("\e[0;92m./fractol Julia 0.285 0.01\e[0m\n");
	ft_putstr("\t\e[0;36mFractol Set\t\t: ");
	ft_putstr("\e[0;92m[Mandelbrot, Julia, Burning_ship,");
	ft_putstr(" Buddhabrot, Phoenix]\e[0m\n");
}

void
	exit_usage(t_data *data)
{
	ft_putstr("\n\t\t\t\e[1;31m! [INVALID USAGE] !\e[0m\n");
	ft_putstr("\n\t\e[0;36mCorrect usage is\t: ");
	ft_putstr("\e[0;92m./fractol <FractalSet>\e[0m\n");
	print_usage_sets();
	end_mlx(data, 1);
}
