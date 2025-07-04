/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_unstuck_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:43:19 by dfasius           #+#    #+#             */
/*   Updated: 2025/05/26 13:43:20 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	ebfs_five(t_direction *step, t_enemy_bfs *bfs)
{
	step->dx = 0;
	step->dy = 0;
	bfs->px = bfs->goal_x;
	bfs->py = bfs->goal_y;
	if (bfs->prev_x[bfs->py][bfs->px] == -1)
		return ;
	while (!(bfs->prev_x[bfs->py][bfs->px] == bfs->start_x
		&& bfs->prev_y[bfs->py][bfs->px] == bfs->start_y))
	{
		bfs->tpx = bfs->prev_x[bfs->py][bfs->px];
		bfs->tpy = bfs->prev_y[bfs->py][bfs->px];
		bfs->px = bfs->tpx;
		bfs->py = bfs->tpy;
		if (bfs->tpx == -1 || bfs->tpy == -1)
			return ;
	}
	step->dx = bfs->px - bfs->start_x;
	step->dy = bfs->py - bfs->start_y;
}

t_direction	find_first_step_to_player(t_var *data, t_enemy_bfs *bfs)
{
	t_direction	step;

	ebfs_one(bfs, data);
	ebfs_two(bfs, data);
	ebfs_three(bfs);
	ebfs_four(data->big_map, bfs);
	ebfs_five(&step, bfs);
	free_ebfs(bfs);
	return (step);
}

void	unstuck_move(t_var *data, t_sprite *sp)
{
	t_enemy_bfs	bfs;
	t_direction	dir;

	bfs = (t_enemy_bfs){0};
	bfs.goal_x = (int)(data->player.px / TILE_SIZE_BIG);
	bfs.goal_y = (int)(data->player.py / TILE_SIZE_BIG);
	bfs.width = data->big_width;
	bfs.height = data->big_height;
	bfs.start_x = sp->spx;
	bfs.start_y = sp->spy;
	dir = find_first_step_to_player(data, &bfs);
	if (dir.dx == 1)
		enemy_right(data, sp);
	else if (dir.dx == -1)
		enemy_left(data, sp);
	else if (dir.dy == 1)
		enemy_down(data, sp);
	else if (dir.dy == -1)
		enemy_up(data, sp);
}
