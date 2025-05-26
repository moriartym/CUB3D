/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:53:33 by dfasius           #+#    #+#             */
/*   Updated: 2025/05/26 13:53:34 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	player_start(t_var *data, int y, int x)
{
	data->player.py = TILE_SIZE * y + TILE_SIZE / 2 - PLAYER_SIZE / 2;
	data->player.px = TILE_SIZE * x + TILE_SIZE / 2 - PLAYER_SIZE / 2;
}
