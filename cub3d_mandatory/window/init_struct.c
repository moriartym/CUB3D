/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:54:16 by dfasius           #+#    #+#             */
/*   Updated: 2025/05/26 13:54:17 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_player(t_var *data)
{
	player_start(data, data->map.ypos, data->map.xpos);
	if (data->map.start_dir == 'N')
		data->player.pa = PI * 1.5;
	else if (data->map.start_dir == 'S')
		data->player.pa = PI / 2;
	else if (data->map.start_dir == 'E')
		data->player.pa = 0;
	else if (data->map.start_dir == 'W')
		data->player.pa = PI + 0.01;
	else
		data->player.pa = 0;
	data->player.pdy = sinf(data->player.pa);
	data->player.pdx = cosf(data->player.pa);
}

void	init_all(t_var *data)
{
	data->move = (t_move){0};
	data->mlx = mlx_init();
	if (!data->mlx)
		handle_error("mlx_init failed", NULL, &data->map, data);
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	if (!data->win)
		handle_error("mlx_new_window failed", NULL, &data->map, data);
	init_player(data);
}
