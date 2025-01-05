#define _GNU_SOURCE
#include "bonus.h"

/**
 ** @name mandelbrot_bonus();
 ** @brief Draw the Mandelbrot fractal using multithreading.
 ** @param t_data *data
 ** @return TRUE [1] on success, FALSE [0] on failure
 **/
int mandelbrot_bonus(t_data *data)
{
    int num_threads;
    int i;
    pthread_t *threads;
    t_thread_data *thread_infos;

    // Initialiser le pool de threads
    initialize_thread_pool(data, data->win_height);

    // Définir les pas pour les axes réel et imaginaire
    data->thread_pool.step_r = (data->math.max_r - data->math.min_r) / (double)data->win_width;
    data->thread_pool.step_i = (data->math.max_i - data->math.min_i) / (double)data->win_height;

    // Déterminer le nombre de threads basés sur les cœurs disponibles
    long n = sysconf(_SC_NPROCESSORS_ONLN);
    if (n < 1)
        n = 1;
    num_threads = (int)n;

    // Allouer la mémoire pour les threads
    threads = malloc(sizeof(pthread_t) * num_threads);
    if (!threads)
    {
        perror("malloc threads");
        pthread_mutex_destroy(&data->thread_pool.mutex);
        return FALSE;
    }

    // Allouer la mémoire pour les informations des threads
    thread_infos = malloc(sizeof(t_thread_data) * num_threads);
    if (!thread_infos)
    {
        perror("malloc thread_infos");
        free(threads);
        pthread_mutex_destroy(&data->thread_pool.mutex);
        return FALSE;
    }

    // Créer les threads
    for (i = 0; i < num_threads; i++)
    {
        thread_infos[i].data = data;
        thread_infos[i].thread_id = i;

        if (pthread_create(&threads[i], NULL, thread_render_generic, &thread_infos[i]) != 0)
        {
            perror("pthread_create");
            // Rejoindre les threads déjà créés
            while (--i >= 0)
                pthread_join(threads[i], NULL);
            free(threads);
            free(thread_infos);
            pthread_mutex_destroy(&data->thread_pool.mutex);
            return FALSE;
        }
    }

    // Rejoindre tous les threads
    for (i = 0; i < num_threads; i++)
        pthread_join(threads[i], NULL);

    // Libérer la mémoire allouée pour les threads
    free(threads);
    free(thread_infos);

    // Détruire le mutex du pool de threads
    pthread_mutex_destroy(&data->thread_pool.mutex);

    return TRUE;
}

