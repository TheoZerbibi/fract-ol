#ifndef COLORS_H
# define COLORS_H

# include "struct.h"

typedef struct s_data			t_data;

typedef struct s_color {
    int r;
    int g;
    int b;
} t_color;

extern t_color palette1[];
extern t_color palette2[];
extern t_color palette3[];

extern int palette1_size;
extern int palette2_size;
extern int palette3_size;

int create_trgb(int t, int r, int g, int b);
int clamp_color(int c);
double lerp(double a, double b, double t);
t_color interpolate(t_color c1, t_color c2, double t);
int make_color(t_data *data, double iteration);
void change_color_shift(t_data *data);
double smooth_iteration(int iteration, double zr, double zi);

#endif
