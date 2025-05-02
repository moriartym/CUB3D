#include "cub3d.h"

void init_move(t_var *data)
{
    data->move.move_w = 0;
    data->move.move_a = 0;
    data->move.move_s = 0;
    data->move.move_d = 0;
}

void init_player(t_var *data)
{
    player_start(data, data->map.ypos, data->map.xpos);
    data->player.pa = P2;
    data->player.pdy = sinf(data->player.pa);
    data->player.pdx = cosf(data->player.pa);
}

void init_all(t_var *data, t_cub *cube)
{
    data->map = cube->map;
    init_move(data);
    init_player(data);
}





