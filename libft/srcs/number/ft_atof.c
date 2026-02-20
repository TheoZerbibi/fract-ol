/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:14:16 by thzeribi          #+#    #+#             */
/*   Updated: 2025/01/05 16:16:27 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int
	skip_spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	return (i);
}

static double
	parse_decimal(const char *str, int *pos)
{
	double	frac;
	double	div;

	frac = 0.0;
	div = 10.0;
	while (str[*pos] >= '0' && str[*pos] <= '9')
	{
		frac += (str[*pos] - '0') / div;
		div *= 10.0;
		(*pos)++;
	}
	return (frac);
}

double
	ft_atof(const char *str)
{
	int		i;
	int		sign;
	double	result;

	i = skip_spaces(str);
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = 0.0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10.0 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		result += parse_decimal(str, &i);
	}
	return (result * sign);
}
