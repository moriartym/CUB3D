/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error_data_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:44:18 by dfasius           #+#    #+#             */
/*   Updated: 2025/05/26 13:44:19 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	free_enemy_gifs(t_var *data)
{
	free_single_img((void **)&data->gif.zero.img, data);
	free_single_img((void **)&data->gif.one.img, data);
	free_single_img((void **)&data->gif.two.img, data);
	free_single_img((void **)&data->gif.three.img, data);
	free_single_img((void **)&data->gif.four.img, data);
	free_single_img((void **)&data->gif.five.img, data);
	free_single_img((void **)&data->gif.six.img, data);
	free_single_img((void **)&data->gif.seven.img, data);
	free_single_img((void **)&data->gif.eight.img, data);
}

void	free_win_gifs(t_var *data)
{
	free_single_img((void **)&data->win_gif.zero.img, data);
	free_single_img((void **)&data->win_gif.one.img, data);
	free_single_img((void **)&data->win_gif.two.img, data);
	free_single_img((void **)&data->win_gif.three.img, data);
}

void	clean_data_texture(t_map *map, t_var *data)
{
	free_single_img((void **)&map->textures[NORTH].attr, data);
	free_single_img((void **)&map->textures[EAST].attr, data);
	free_single_img((void **)&map->textures[SOUTH].attr, data);
	free_single_img((void **)&map->textures[WEST].attr, data);
	free_single_img((void **)&map->textures[FLOOR].attr, data);
	free_single_img((void **)&map->textures[CEILING].attr, data);
	free_single_img((void **)&map->textures[DOOR_O].attr, data);
	free_single_img((void **)&map->textures[DOOR_C].attr, data);
	free_single_img((void **)&map->textures[DOOR_S].attr, data);
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
	free_enemy_gifs(data);
	free_win_gifs(data);
	free_state_images(data);
	ft_free_ptr((void **)&data->sprites);
	free_single_img(&data->image.img, data);
	clean_data_texture(&data->map, data);
	ft_free_2d(&data->save.map);
	ft_free_ptr((void **)&data->save.sprites);
	ft_free_2d(&data->big_map);
	close_mlx(data);
}
