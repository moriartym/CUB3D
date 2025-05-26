/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_win_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:49:25 by dfasius           #+#    #+#             */
/*   Updated: 2025/05/26 13:49:27 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	load_win_gifs(t_var *data)
{
	load_single_image(data, &data->win_gif.zero,
		"textures_bonus/win/sayuri-1.xpm");
	load_single_image(data, &data->win_gif.one,
		"textures_bonus/win/sayuri-2.xpm");
	load_single_image(data, &data->win_gif.two,
		"textures_bonus/win/sayuri-3.xpm");
	load_single_image(data, &data->win_gif.three,
		"textures_bonus/win/sayuri-4.xpm");
}

void	change_win_tile(t_var *data, int x, int y, bool change)
{
	if (!change)
		return ;
	data->map.arr[y][x] = WIN_BLOCK;
	data->win_sprite.x = x * TILE_SIZE + 0.5 * TILE_SIZE;
	data->win_sprite.y = y * TILE_SIZE + 0.5 * TILE_SIZE;
}

void	change_to_win(t_var *data, t_bfs *bfs, int index)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (bfs->reachable[y][x] == true
				&& data->map.arr[y][x] == EMPTY_SPACE
				&& !(y == bfs->ipy && x == bfs->ipx))
			{
				change_win_tile(data, x, y, i == index);
				if (i == index)
					return ;
				i++;
			}
			x++;
		}
		y++;
	}
}

void	place_winning_tiles(t_var *data)
{
	t_bfs	bfs;
	int		index;

	bfs = (t_bfs){0};
	do_bfs(data, &bfs);
	if (bfs.empty_spaces > 1)
	{
		index = rand() % bfs.empty_spaces;
		change_to_win(data, &bfs, index);
	}
	else
		printf("Sorry, no winning tiles for this game.\n");
	free_enemy_bfs(data, &bfs);
}
