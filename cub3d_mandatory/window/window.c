/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:54:22 by dfasius           #+#    #+#             */
/*   Updated: 2025/05/26 13:54:23 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	close_window(t_var *data)
{
	printf("Thanks for playing, bye bye! 👋🎮😊\n");
	handle_error_noexit(NULL, NULL, &data->map, data);
	exit(0);
	return (0);
}

int	render(t_var *data)
{
	update_movement(data);
	draw_rays(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
	return (0);
}

int	create_visual(t_map *map)
{
	t_var	data;

	data = (t_var){0};
	data.map = *map;
	init_all(&data);
	create_image_buffer(&data);
	load_textures(&data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_hook(data.win, DestroyNotify,
		StructureNotifyMask, &close_window, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
	mlx_loop(data.mlx);
	return (0);
}
