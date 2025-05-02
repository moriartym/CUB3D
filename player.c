#include "cub3d.h"

void player_start(t_var *data, int y, int x)
{
    data->player.py = TILE_SIZE * y + TILE_SIZE / 2 - PLAYER_SIZE / 2;
    data->player.px = TILE_SIZE * x + TILE_SIZE / 2 - PLAYER_SIZE / 2;
}

void draw_player(t_var *data)
{
    int by;
    int bx;

    by = - PLAYER_SIZE/2;
    while (by < PLAYER_SIZE)
    {
        bx = - PLAYER_SIZE/2;
        while (bx < PLAYER_SIZE)
        {
            my_mlx_pixel_put(&data->image, (int)(data->player.px + bx), (int)(data->player.py + by), PLAYER_COLOR);
            bx++;
        }
        by++;
    }
}