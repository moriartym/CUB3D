#include "cub3d.h"

int handle_keypress(int keysym, t_var *data)
{
    if (keysym == XK_Escape)
        close_window(data);
    else if (keysym == XK_a)
        data->move.move_a = 1;
    else if (keysym == XK_d)
        data->move.move_d = 1;
    else if (keysym == XK_w)
        data->move.move_w = 1;
    else if (keysym == XK_s)
        data->move.move_s = 1;
    return 0;
}

int handle_keyrelease(int keysym, t_var *data)
{
    if (keysym == XK_a)
        data->move.move_a = 0;
    else if (keysym == XK_d)
        data->move.move_d = 0;
    else if (keysym == XK_w)
        data->move.move_w = 0;
    else if (keysym == XK_s)
        data->move.move_s = 0;
    return 0;
}

double get_delta_time(t_var *data)
{
    struct timeval current_time;
    double delta_time;

    gettimeofday(&current_time, NULL);
    delta_time = (current_time.tv_sec - data->last_time.tv_sec) +
                 (current_time.tv_usec - data->last_time.tv_usec) / 1000000.0;
    data->last_time = current_time;
    if (delta_time > MAX_DELTA_TIME)
        delta_time = MAX_DELTA_TIME;
    return delta_time;
}

float normalize_radians(float angle)
{
    while (angle < 0)
        angle += 2 * PI;
    while (angle >= 2 * PI)
        angle -= 2 * PI;
    return angle;
}

void update_movement(t_var *data)
{
    double delta_time;

    delta_time = get_delta_time(data);
    if (data->move.move_a)
        data->player.pa -= ROTATION_SPEED * delta_time;
    if (data->move.move_d)
        data->player.pa += ROTATION_SPEED * delta_time;
    data->player.pa = normalize_radians(data->player.pa);
    data->player.pdy = sinf(data->player.pa) * MOVEMENT_SPEED * delta_time;
    data->player.pdx = cosf(data->player.pa) * MOVEMENT_SPEED * delta_time;
    if (data->move.move_w)
    {
        data->player.px += data->player.pdx;
        data->player.py += data->player.pdy;
    }
    if (data->move.move_s)
    {
        data->player.px -= data->player.pdx;
        data->player.py -= data->player.pdy;
    }
}
