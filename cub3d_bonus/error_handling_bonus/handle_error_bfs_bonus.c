/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error_bfs_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:43:48 by dfasius           #+#    #+#             */
/*   Updated: 2025/05/26 13:43:49 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	free_enemy_bfs(t_var *data, t_bfs *bfs)
{
	ft_free_ptr((void **)&bfs->queue_x);
	ft_free_ptr((void **)&bfs->queue_y);
	ft_free_2d_ptr((void ***) &bfs->reachable, data->map.height);
}

void	enemy_bfs_error(t_var *data, t_bfs *bfs, char *msg)
{
	free_enemy_bfs(data, bfs);
	handle_error(msg, NULL, &data->map, data);
}

void	free_ebfs(t_enemy_bfs *bfs)
{
	ft_free_ptr((void **)&bfs->queue_x);
	ft_free_ptr((void **)&bfs->queue_y);
	ft_free_2d_ptr((void ***)&bfs->visited, bfs->height);
	ft_free_2d_ptr((void ***)&bfs->prev_x, bfs->height);
	ft_free_2d_ptr((void ***)&bfs->prev_y, bfs->height);
}

void	enemy_move_bfs_error(t_var *data, t_enemy_bfs *bfs, char *msg)
{
	free_ebfs(bfs);
	handle_error(msg, NULL, &data->map, data);
}
