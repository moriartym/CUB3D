#include "cub3d.h"

void draw_tile(t_img *img, int x, int y, int color)
{
    int by;
    int bx;

    by = 0;
    while (by < TILE_SIZE)
    {
        bx = 0;
        while (bx < TILE_SIZE)
        {
            my_mlx_pixel_put(img, x + bx, y + by, color);
            bx++;
        }
        by++;
    }
}

void draw_map(t_var *data, int x, int y)
{
    int draw_x;
    int draw_y;
    char tile;
    int color;

    tile = data->map.arr[y][x];
    color = EMPTY_COLOR;
    if (tile == '0')
        color = EMPTY_COLOR;
    else if (tile == '1')
        color = WALL_COLOR;
    else
        color = EMPTY_COLOR;
    draw_x = x * TILE_SIZE;
    draw_y = y * TILE_SIZE;
    draw_tile(&data->image, draw_x, draw_y, color);
}

void    create_minimap(t_var *data)
{
    int y;
    int x;
    
    y = 0;
    while (y < data->map.height)
    {
        x = 0;
        while (x < data->map.max_length - 1)
        {
            draw_map(data, x, y);
            x++;
        }
        y++;
    }
}
