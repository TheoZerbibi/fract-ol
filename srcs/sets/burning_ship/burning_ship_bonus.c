#define _GNU_SOURCE
#include "bonus.h"

/**
 ** @name burningship_bonus();
 ** @brief Draw the Burning Ship fractal using multithreading.
 ** @param t_data *data
 ** @return TRUE [1] on success, FALSE [0] on failure
 **/
int burningship_bonus(t_data *data)
{
    (void)data;
    // int num_threads;
    // int i, lines_per_thread, start;
    // pthread_t *threads;
    // t_thread_data *thread_infos;

    // double step_r = (data->math.max_r - data->math.min_r) / (double)data->win_width;
    // double step_i = (data->math.max_i - data->math.min_i) / (double)data->win_height; // Correction ici
    // long n = sysconf(_SC_NPROCESSORS_ONLN);
    // if (n < 1)
    //     n = 1;
    // num_threads = (int)n;
    // threads = malloc(sizeof(pthread_t) * num_threads);
    // if (!threads)
    // {
    //     perror("malloc threads");
    //     return FALSE;
    // }
    // thread_infos = malloc(sizeof(t_thread_data) * num_threads);
    // if (!thread_infos)
    // {
    //     perror("malloc thread_infos");
    //     free(threads);
    //     return FALSE;
    // }
    // lines_per_thread = data->win_height / num_threads;
    // start = 0;
    // i = -1;
    // while (++i < num_threads)
    // {
    //     thread_infos[i].data = data;
    //     thread_infos[i].start_line = start;
    //     thread_infos[i].end_line = start + lines_per_thread;
    //     if (i == num_threads - 1)
    //         thread_infos[i].end_line = data->win_height;
    //     thread_infos[i].step_r = step_r;
    //     thread_infos[i].step_i = step_i;
    //     thread_infos[i].thread_id = i;

    //     if (pthread_create(&threads[i], NULL, thread_render_generic, &thread_infos[i]) != 0)
    //     {
    //         perror("pthread_create");
    //         while (--i >= 0)
    //             pthread_join(threads[i], NULL);
    //         free(threads);
    //         free(thread_infos);
    //         return FALSE;
    //     }
    //     start += lines_per_thread;
    // }
    // i = -1;
    // while (++i < num_threads)
    //     pthread_join(threads[i], NULL);

    // free(threads);
    // free(thread_infos);
    return TRUE;
}
