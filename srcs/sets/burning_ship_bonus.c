#define _GNU_SOURCE
#include "fractol.h"
#include <pthread.h>
#include <unistd.h>
#include <sched.h>
#include <math.h>
#include <stdio.h>

/**
 ** @name inside_main_cardioid();
 ** @brief Check if a point is inside the main cardioid of the Burning Ship fractal.
 ** @param double cr Real part
 ** @param double ci Imaginary part
 ** @return 1 if inside, 0 otherwise
 **/
static inline int
inside_main_cardioid(double cr, double ci)
{
    double pr = cr - 0.25;
    double q = pr * pr + ci * ci;
    return (q * (q + pr) <= 0.25 * ci * ci);
}

/**
 ** @name inside_period2_bulb();
 ** @brief Check if a point is inside the period-2 bulb of the Burning Ship fractal.
 ** @param double cr Real part
 ** @param double ci Imaginary part
 ** @return 1 if inside, 0 otherwise
 **/
static inline int
inside_period2_bulb(double cr, double ci)
{
    double tmp = cr + 1.0;
    return ((tmp * tmp + ci * ci) <= 1.0 / 16.0);
}

/**
 ** @name set_thread_affinity();
 ** @brief Set the CPU affinity for a thread to optimize cache usage.
 ** @param int thread_id Identifier of the thread
 **/
static void
set_thread_affinity(int thread_id)
{
    cpu_set_t cpuset;
    long n = sysconf(_SC_NPROCESSORS_ONLN);
    if (n < 1)
        n = 1;
    CPU_ZERO(&cpuset);
    CPU_SET(thread_id % n, &cpuset);
    if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) != 0)
    {
        perror("pthread_setaffinity_np");
    }
}

/**
 ** @name thread_render();
 ** @brief Function executed by each thread to render a portion of the Burning Ship fractal.
 ** @param void *arg Pointer to thread data
 ** @return NULL
 **/
static void *
thread_render(void *arg)
{
    t_thread_data  *info = (t_thread_data *)arg;
    set_thread_affinity(info->thread_id);
    int x, y;
    double pr, pi;
    int it;

    y = info->start_line - 1;
    while (++y < info->end_line)
    {
        pi = info->data->math.max_i - y * info->step_i;
        x = -1;
        while (++x < info->data->win_width)
        {
            pr = info->data->math.min_r + x * info->step_r;
            if (inside_main_cardioid(pr, pi) || inside_period2_bulb(pr, pi))
            {
                my_mlx_pixel_put(&info->data->image, x, y, create_trgb(0, 0, 0, 0));
                continue;
            }
            it = is_burningship(info->data, pr, pi);
            if (it != -1)
                my_mlx_pixel_put(&info->data->image, x, y, make_color(info->data, it));
            else
                my_mlx_pixel_put(&info->data->image, x, y, create_trgb(0, 0, 0, 0));
        }
    }
    return (NULL);
}

/**
 ** @name burningship_bonus();
 ** @brief Draw the Burning Ship fractal using multithreading.
 ** @param t_data *data
 ** @return TRUE [1] on success, FALSE [0] on failure
 **/
int
burningship_bonus(t_data *data)
{
    int              num_threads;
    int              i, lines_per_thread, start;
    pthread_t        *threads;
    t_thread_data    *thread_infos;
    double           step_r;
    double           step_i;

    step_r = (data->math.max_r - data->math.min_r) / (double)data->win_width;
    step_i = (data->math.max_i - data->math.min_i) / (double)data->win_height;

    long n = sysconf(_SC_NPROCESSORS_ONLN);
    if (n < 1)
        n = 1;
    num_threads = (int)n;
    threads = malloc(sizeof(pthread_t) * num_threads);
    if (!threads)
    {
        perror("malloc threads");
        return (FALSE);
    }
    thread_infos = malloc(sizeof(t_thread_data) * num_threads);
    if (!thread_infos)
    {
        perror("malloc thread_infos");
        free(threads);
        return (FALSE);
    }

    lines_per_thread = data->win_height / num_threads;
    start = 0;
    i = -1;
    while (++i < num_threads)
    {
        thread_infos[i].data = data;
        thread_infos[i].start_line = start;
        thread_infos[i].end_line = start + lines_per_thread;
        if (i == num_threads - 1)
            thread_infos[i].end_line = data->win_height;
        thread_infos[i].step_r = step_r;
        thread_infos[i].step_i = step_i;
        thread_infos[i].thread_id = i;

        if (pthread_create(&threads[i], NULL, thread_render, &thread_infos[i]) != 0)
        {
            perror("pthread_create");
            while (--i >= 0)
                pthread_join(threads[i], NULL);
            free(threads);
            free(thread_infos);
            return (FALSE);
        }
        start += lines_per_thread;
    }
    i = -1;
    while (++i < num_threads)
        pthread_join(threads[i], NULL);
    free(threads);
    free(thread_infos);
    return (TRUE);
}