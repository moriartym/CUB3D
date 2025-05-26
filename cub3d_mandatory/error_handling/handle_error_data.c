/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:52:10 by dfasius           #+#    #+#             */
/*   Updated: 2025/05/26 13:52:11 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	clean_data_texture(t_map *map, t_var *data)
{
	free_single_img((void **)&map->textures[NORTH].attr, data);
	free_single_img((void **)&map->textures[EAST].attr, data);
	free_single_img((void **)&map->textures[SOUTH].attr, data);
	free_single_img((void **)&map->textures[WEST].attr, data);
	free_single_img((void **)&map->textures[FLOOR].attr, data);
	free_single_img((void **)&map->textures[CEILING].attr, data);
}

void	close_mlx(t_var *data)
{
	if (data->mlx && data->win)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
}

void	clean_data(t_var *data)
{
	free_single_img(&data->image.img, data);
	clean_data_texture(&data->map, data);
	close_mlx(data);
}
