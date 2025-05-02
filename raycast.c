#include "cub3d.h"


void draw_line(t_var *data, int x0, int y0, int x1, int y1, int color)
{
    float dx = x1 - x0;
    float dy = y1 - y0;

    int steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);

    float x_inc = dx / steps;
    float y_inc = dy / steps;

    float x = x0;
    float y = y0; 

    for (int i = 0; i <= steps; i++)
    {
        my_mlx_pixel_put(&data->image, (int)x, (int) y, color);
        x += x_inc;
        y += y_inc;
    }
}


void draw_rays(t_var *data)
{
    t_ray ray;

    ray = (t_ray){0};
    ray.ra = normalize_radians(data->player.pa - (PI/6));
    ray.r = 0;
    while (ray.r < NUM_RAYS)
    {
        
        // vertical
        ray.dof = 0;
        ray.side = 0;
        ray.disV = 100000;
        ray.tan = - tan(ray.ra);
        if (cos(ray.ra) > 0.001)
        {
            ray.rx = (((int)data->player.px >> 6) << 6) + 64;
            ray.ry= (data->player.px - ray.rx) * ray.tan + data->player.py;
            ray.xo= 64;
            ray.yo= - ray.xo * ray.tan;
        }
        else if (cos(ray.ra) < -0.001)
        {
            ray.rx = (((int)data->player.px >> 6) << 6) - 0.0001;
            ray.ry= (data->player.px - ray.rx) * ray.tan + data->player.py;
            ray.xo= - 64;
            ray.yo= - ray.xo * ray.tan;
        }
        else
        {
            ray.rx = data->player.px;
            ray.ry = data->player.py;
            ray.dof = 8;
        }
        while (ray.dof < 8)
        {
            ray.mx = (int) (ray.rx) >> 6;
            ray.my = (int) (ray.ry) >> 6;
            ray.mp = ray.my * MAP_WIDTH + ray.mx;
            if (ray.mx >= 0 && ray.my >= 0 && ray.mx < MAP_WIDTH && ray.my < MAP_HEIGHT && data->map.arr[ray.my][ray.mx] == '1')
            {
                ray.dof = 8;
                ray.vx = ray.rx;
                ray.vy = ray.ry;
                ray.disV = sqrt(pow(ray.rx - data->player.px, 2) + pow(ray.ry - data->player.py, 2));
                }
            else
            {
                ray.rx += ray.xo;
                ray.ry += ray.yo;
                ray.dof += 1;
            }
        }
    //    Horizontal
        ray.dof = 0;
        ray.disH = 100000;
        ray.tan =  1 / ray.tan;

        if (sin(ray.ra) < -0.001)
        {
            
            ray.ry = (((int)data->player.py >> 6) << 6) - 0.0001;
            ray.rx = (data->player.py - ray.ry) * ray.tan + data->player.px;
            ray.yo = -64;
            ray.xo = -ray.yo * ray.tan;
        }
        else if (sin(ray.ra) > 0.001)
        {
            ray.ry = (((int)data->player.py >> 6) << 6) + 64;
            ray.rx = (data->player.py - ray.ry) * ray.tan + data->player.px;
            ray.yo = 64;
            ray.xo = -ray.yo * ray.tan;
        }
        else
        {
            ray.rx = data->player.px;
            ray.ry = data->player.py;
            ray.dof = 8;
        }
        while (ray.dof < 8)
        {
            ray.mx=(int)(ray.rx)>>6;
            ray.my=(int)(ray.ry)>>6;
            ray.mp=ray.my*MAP_HEIGHT+ray.mx;
            if (ray.mx >= 0 && ray.my >= 0 && ray.mx < MAP_WIDTH && ray.my < MAP_HEIGHT && data->map.arr[ray.my ][ray.mx] == '1')
            {
                ray.dof = 8;
                ray.disH = sqrt(pow(ray.rx - data->player.px, 2) + pow(ray.ry - data->player.py, 2));
    
            }
            else
            {
                    ray.rx += ray.xo;
                    ray.ry += ray.yo;
                    ray.dof += 1;
            }

        }
        if (ray.disH < ray.disV)
        {
            ray.side = 1; 
        }
        else
        {
            ray.rx = ray.vx;
            ray.ry = ray.vy;
            ray.side = 0;
        }

        int x1 = (int)data->player.px;
        int y1 = (int)data->player.py;
        int x2 = (int)ray.rx;
        int y2 = (int)ray.ry;

        draw_line(data, x1, y1, x2, y2, RAYCAST_COLOR);


        ray.ra += (PI / 3) / NUM_RAYS;
        ray.ra = normalize_radians(ray.ra);
        ray.r++;

    }
}