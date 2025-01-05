#define _GNU_SOURCE
#include "bonus.h"
#include <stdio.h>

void initialize_thread_pool(t_data *data, int total_lines)
{
	if (pthread_mutex_init(&data->thread_pool.mutex, NULL) != 0)
	{
		perror("pthread_mutex_init");
		exit_init(data);
	}
	data->thread_pool.current_line = 0;
	data->thread_pool.total_lines = total_lines;
}

void set_thread_affinity(int thread_id, int num_cores)
{
	cpu_set_t cpuset;
	pthread_t thread = pthread_self();
	CPU_ZERO(&cpuset);
	CPU_SET(thread_id % num_cores, &cpuset); // Assigner le thread_id au CPU correspondant

	int s = pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
	if (s != 0)
	{
		fprintf(stderr, "Error setting thread affinity: %d\n", s);
		// Vous pouvez choisir de quitter ou de continuer sans affinité
	}
}

// Fonction de rendu générique pour les threads
void *thread_render_generic(void *arg)
{
	t_thread_data *info = (t_thread_data *)arg;
	t_data *data = info->data;
	int y, x;
	double pr, pi, it;
	unsigned int color;
	int num_cores = sysconf(_SC_NPROCESSORS_ONLN);

	// Définir l'affinité du thread au CPU correspondant
	set_thread_affinity(info->thread_id, num_cores);

	while (1)
	{
		// Récupérer la prochaine ligne à traiter de manière sécurisée
		pthread_mutex_lock(&data->thread_pool.mutex);
		y = data->thread_pool.current_line++;
		pthread_mutex_unlock(&data->thread_pool.mutex);

		// Vérifier si toutes les lignes ont été traitées
		if (y >= data->thread_pool.total_lines)
			break;

		pi = data->math.min_i + y * data->thread_pool.step_i;

		for (x = 0; x < data->win_width; x++)
		{
			pr = data->math.min_r + x * data->thread_pool.step_r;
			it = data->fractal.iterate(data, pr, pi);

			if (it >= (double)data->fractal.max_iterations)
				color = create_trgb(0, 0, 0, 0);
			else
				color = make_color(data, it);

			data->image.buffer[y * data->win_width + x] = color;
		}

		// Debugging : Afficher la progression
		// if (y % 100 == 0)
		// 	printf("Thread %d a traité la ligne %d\n", info->thread_id, y);
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
