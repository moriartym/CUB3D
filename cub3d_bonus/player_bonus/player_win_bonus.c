/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_win_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:47:51 by dfasius           #+#    #+#             */
/*   Updated: 2025/05/26 13:47:53 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	draw_win(t_var *data)
{
	t_edraw	draw;

	draw = (t_edraw){0};
	init_enemy_draw(data, &draw);
	if (enemy_size(data, &draw, &data->win_sprite))
		return ;
	draw.frame = draw.anim_sequence[data->current_anim_index];
	draw.cur_img = NULL;
	if (draw.frame % 4 == 0)
		draw.cur_img = &data->win_gif.zero;
	if (draw.frame % 4 == 1)
		draw.cur_img = &data->win_gif.one;
	if (draw.frame % 4 == 2)
		draw.cur_img = &data->win_gif.two;
	if (draw.frame % 4 == 3)
		draw.cur_img = &data->win_gif.three;
	screen_draw(data, &draw);
}

void	win(t_var *data)
{
	int	px;
	int	py;

	px = (int)(data->player.px / TILE_SIZE);
	py = (int)(data->player.py / TILE_SIZE);
	if (data->map.arr[py][px] == WIN_BLOCK)
	{
		printf("🎉 You win!\nPress R to play again\n");
		data->state.state = WIN;
	}
}
