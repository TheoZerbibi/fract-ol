#define _GNU_SOURCE
#include "bonus.h"

void set_thread_affinity(int thread_id)
{
	cpu_set_t cpuset;
	long n = sysconf(_SC_NPROCESSORS_ONLN);
	if (n < 1)
		n = 1;
	CPU_ZERO(&cpuset);
	CPU_SET(thread_id % n, &cpuset);
	if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) != 0)
		perror("pthread_setaffinity_np");
}

void *thread_render_generic(void *arg)
{
	int x, y;
	double it;

	t_thread_data *info = (t_thread_data *)arg;
	set_thread_affinity(info->thread_id);
	t_inside_func inside_func = NULL;
	t_iterate_func iterate_func = NULL;
	if (info->data->set == MANDELBROT)
	{
		inside_func = inside_main_cardioid;
		iterate_func = is_mandelbrot_smooth;
	}
	else if (info->data->set == BURNING_SHIP)
		iterate_func = is_burningship_smooth;
	y = info->start_line - 1;
	while (++y < info->end_line)
	{
		double pi;
		if (info->data->set == BURNING_SHIP)
			pi = info->data->math.min_i + y * info->step_i;
		else
			pi = info->data->math.max_i - y * info->step_i;

		x = -1;
		while (++x < info->data->win_width)
		{
			double pr = info->data->math.min_r + x * info->step_r;
			if (inside_func && (inside_func(pr, pi)))
			{
				my_mlx_pixel_put(&info->data->image, x, y, create_trgb(0, 0, 0, 0));
				continue;
			}

			it = iterate_func(info->data, pr, pi);
			if (it >= info->data->fractal.max_iterations)
				my_mlx_pixel_put(&info->data->image, x, y, create_trgb(0, 0, 0, 0));
			else
				my_mlx_pixel_put(&info->data->image, x, y, make_color(info->data, it));
		}
	}
	return NULL;
}

int inside_main_cardioid(double cr, double ci)
{
	double pr2 = cr - 0.25;
	double q = pr2 * pr2 + ci * ci;
	return (q * (q + (cr - 0.25)) <= 0.25 * ci * ci);
}

int inside_period2_bulb(double cr, double ci)
{
	double tmp = (cr + 1.0);
	return ((tmp * tmp + ci * ci) <= 1.0 / 16.0);
}
