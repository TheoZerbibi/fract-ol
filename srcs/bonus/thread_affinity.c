/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_affinity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:13:56 by thzeribi          #+#    #+#             */
/*   Updated: 2026/02/19 12:18:03 by thzeribi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

void
	set_thread_affinity(int thread_id)
{
	cpu_set_t	cpuset;
	long		n;

	n = sysconf(_SC_NPROCESSORS_ONLN);
	if (n < 1)
		n = 1;
	CPU_ZERO(&cpuset);
	CPU_SET(thread_id % n, &cpuset);
	pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
}

void
	fill_thread_infos(t_thread_data *info, t_data *data, double *step)
{
	int	i;
	int	lpt;
	int	start;

	lpt = data->win_height / info[0].thread_id;
	start = 0;
	i = 0;
	while (i < info[0].thread_id)
	{
		info[i].data = data;
		info[i].start_line = start;
		info[i].end_line = start + lpt;
		if (i == info[0].thread_id - 1)
			info[i].end_line = data->win_height;
		info[i].step_r = step[0];
		info[i].step_i = step[1];
		start += lpt;
		i++;
	}
}
