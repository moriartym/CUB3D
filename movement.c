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
    else if (keysym == XK_Left)
        data->move.move_al = 1;
    else if (keysym == XK_Right)
        data->move.move_ar = 1;
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
    else if (keysym == XK_Left)
        data->move.move_al = 0;
    else if (keysym == XK_Right)
        data->move.move_ar = 0;
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

int is_wall(t_var *data, int x, int y)
{
    int map_x;
    int map_y;
    int offset;

    map_x = (int)((x) / TILE_SIZE);
    map_y = (int)((y) / TILE_SIZE);
    if (map_x >= 0 && map_x < MAP_WIDTH && map_y >= 0 && map_y < MAP_HEIGHT)
        return (data->map.arr[map_y][map_x] == '1');
    return 0;
}

void update_movement(t_var *data)
{
    //make it can sliding
    double delta_time;
    float new_px;
    float new_py;

    delta_time = get_delta_time(data);
    if (data->move.move_al)
        data->player.pa -= ROTATION_SPEED * delta_time;
    if (data->move.move_ar)
        data->player.pa += ROTATION_SPEED * delta_time;
    data->player.pa = normalize_radians(data->player.pa);
    data->player.pdy = sinf(data->player.pa) * MOVEMENT_SPEED * delta_time;
    data->player.pdx = cosf(data->player.pa) * MOVEMENT_SPEED * delta_time;
    if (data->move.move_w)
    {
        new_px = data->player.px + data->player.pdx;
        new_py = data->player.py + data->player.pdy;
        if (!is_wall(data, new_px, new_py))
        {
            data->player.px = new_px;
            data->player.py = new_py;
        }
    }
    if (data->move.move_s)
    {
        new_px = data->player.px - data->player.pdx;
        new_py = data->player.py - data->player.pdy;
        if (!is_wall(data, new_px, new_py ))
        {
            data->player.px = new_px;
            data->player.py = new_py;
        }
    }
    if (data->move.move_a)
    {
        new_px = data->player.px - data->player.pdy;
        new_py = data->player.py + data->player.pdx;
        if (!is_wall(data, new_px, new_py ))
        {
            data->player.px = new_px;
            data->player.py = new_py;
        }
    }
    if (data->move.move_d)
    {
        new_px = data->player.px + data->player.pdy;
        new_py = data->player.py - data->player.pdx;
        if (!is_wall(data, new_px, new_py ))
        {
            data->player.px = new_px;
            data->player.py = new_py;
        }
    }
}
