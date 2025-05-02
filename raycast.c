#include "cub3d.h"

void draw_line(t_var *data, t_line line, int color)
{
    int i;

    i = 0;
    line.dx = line.rx - data->player.px;
    line.dy = line.ry - data->player.py;
    if (fabs(line.dx) > fabs(line.dy))
        line.steps =  fabs(line.dx);
    else
        line.steps =  fabs(line.dy);
    line.x_inc = line.dx / line.steps;
    line.y_inc = line.dy / line.steps;
    while (i <= line.steps)
    {
        my_mlx_pixel_put(&data->image, (int)line.px, (int) line.py, color);
        line.px += line.x_inc;
        line.py += line.y_inc;
        i++;
    }
}

void cast_rays(t_var *data, t_ray *ray)
{
    t_line line;

    if (ray->disH < ray->disV)
        ray->side = 1; 
    else
    {
        ray->disH = ray->disV;
        ray->rx = ray->vx;
        ray->ry = ray->vy;
    }
    line = (t_line){0};
    line.px = (int)data->player.px;
    line.py = (int)data->player.py;
    line.rx = (int)ray->rx;
    line.ry = (int)ray->ry;
    draw_line(data, line, RAYCAST_COLOR);
}

void draw_3d_helper(t_var *data, t_ray *ray, int lineOff, int lineH)
{
    int color = ray->side == 1 ? 0xCCCCCC : 0xAAAAAA;
    int x, y, w;

    w = 0;
    while (w < STRIP_WIDTH)
    {
        x = ray->r * STRIP_WIDTH + (MAP_WIDTH * TILE_SIZE) + w;

        if (x < WINDOW_WIDTH)
        {
            y = 0;
            while (y < WINDOW_HEIGHT)
            {
                if (y < lineOff)
                    my_mlx_pixel_put(&data->image, x, y, CEILING_COLOR);
                else if (y >= lineOff && y < lineOff + lineH)
                    my_mlx_pixel_put(&data->image, x, y, color);
                else
                    my_mlx_pixel_put(&data->image, x, y, FLOOR_COLOR);
                y++;
            }
        }
        w++;
    }
}


void draw_3d(t_var *data, t_ray *ray)
{
    double corrected_dist;
    int lineH;
    int lineOff;
    int color;
    int x, y, w;

    corrected_dist = ray->disH * cos(normalize_radians(data->player.pa - ray->ra));
    lineH = (TILE_SIZE * WINDOW_HEIGHT)/(corrected_dist);
    if (lineH > WINDOW_HEIGHT)
        lineH= WINDOW_HEIGHT;
    lineOff = (WINDOW_HEIGHT / 2) - (lineH >> 1);
    draw_3d_helper(data, ray, lineOff, lineH);
}

void draw_rays(t_var *data)
{
    t_ray ray;

    ray = (t_ray){0};
    ray.ra = normalize_radians(data->player.pa - (PI/6));
    ray.r = 0;
    while (ray.r < NUM_RAYS)
    {
        ray.disV = 100000;
        ray.disH = 100000;
        ray.side = 0;
        ray.dof = 0;
        ray.tan = - tan(ray.ra);
        cast_vertical(data, &ray);
        ray.dof = 0;
        ray.tan =  1 / ray.tan;
        cast_horizontal(data, &ray);
        cast_rays(data, &ray);
        draw_3d(data, &ray);
        ray.ra += (PI / 3) / NUM_RAYS;
        ray.ra = normalize_radians(ray.ra);
        ray.r++;
    }
}
