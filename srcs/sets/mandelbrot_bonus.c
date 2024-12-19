#define _GNU_SOURCE
#include "fractol.h"
#include <pthread.h>
#include <unistd.h>
#include <sched.h>
#include <math.h>

static inline int
inside_main_cardioid(double cr, double ci)
{
    // double pr;
    // double p;

    // Test de la cardioïde principale
    // p = distance entre c et 1/4 + 0i
    // pr = cr - 0.25;
    // p = pr * pr + ci * ci;
    // Test : c est à l’intérieur de la cardioïde si :
    // p*(p + (cr - 0.25)) <= 0.25 * ci^2  [Formule classique]
    // Une autre formule équivalente plus répandue :
    // p = sqrt((cr - 1/4)^2 + ci^2)
    // c est dans la cardioïde si cr < p - 2*p*p + 1/4
    // Mais la première forme est plus directe.
    // Ici, on utilise une version connue :
    double pr2 = cr - 0.25;
    double q = pr2 * pr2 + ci * ci;
    return (q * (q + (cr - 0.25)) <= 0.25 * ci * ci);
}

static inline int
inside_period2_bulb(double cr, double ci)
{
    // Test du bulbe de période-2
    double tmp = (cr + 1.0);
    return ((tmp * tmp + ci * ci) <= 1.0 / 16.0);
}

static void
set_thread_affinity(int thread_id)
{
    cpu_set_t cpuset;
    long n = sysconf(_SC_NPROCESSORS_ONLN);
    if (n < 1)
        n = 1;
    CPU_ZERO(&cpuset);
    CPU_SET(thread_id % n, &cpuset);
    pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
}

static void
*thread_render(void *arg)
{
    t_thread_data  *info;
    int            x;
    int            y;
    double         pr;
    double         pi;

    info = (t_thread_data *)arg;
    set_thread_affinity(info->thread_id); // Assigne le thread à un cœur.

    y = info->start_line - 1;
    while (++y < info->end_line)
    {
        pi = info->data->math.max_i + (double)y * info->step_i;
        x = -1;
        while (++x < info->data->win_width)
        {
            pr = info->data->math.min_r + (double)x * info->step_r;

            if (inside_main_cardioid(pr, pi) || inside_period2_bulb(pr, pi))
            {
                my_mlx_pixel_put(&info->data->image, x, y, create_trgb(0,0,0,0));
                continue;
            }
            int it = is_mandelbrot(info->data, pr, pi);
            if (it == -1)
                my_mlx_pixel_put(&info->data->image, x, y, create_trgb(0, 0, 0, 0));
            else
                my_mlx_pixel_put(&info->data->image, x, y, make_color(info->data, it));
        }
    }
    return (NULL);
}

int
mandelbrot_bonus(t_data *data)
{
    int              i;
    int              num_threads;
    pthread_t        *threads;
    t_thread_data    *thread_infos;
    double           step_r;
    double           step_i;
    int              lines_per_thread;
    int              start;

    step_r = (data->math.max_r - data->math.min_r) / (double)data->win_width;
    step_i = (data->math.min_i - data->math.max_i) / (double)data->win_height;

    // Déterminer dynamiquement le nombre de threads
    // Utilisation du nombre de cœurs logiques
    long n = sysconf(_SC_NPROCESSORS_ONLN);
    if (n < 1)
        n = 1;
    num_threads = (int)n;

    threads = malloc(sizeof(pthread_t) * num_threads);
    thread_infos = malloc(sizeof(t_thread_data) * num_threads);
    if (!threads || !thread_infos)
        return (FALSE);

    lines_per_thread = data->win_height / num_threads;
    i = -1;
    start = 0;
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
        pthread_create(&threads[i], NULL, thread_render, &thread_infos[i]);
        start += lines_per_thread;
    }

    i = -1;
    while (++i < num_threads)
        pthread_join(threads[i], NULL);

    free(threads);
    free(thread_infos);
    return (TRUE);
}