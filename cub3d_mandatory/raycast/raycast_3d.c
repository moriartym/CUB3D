/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:53:50 by dfasius           #+#    #+#             */
/*   Updated: 2025/05/26 13:53:51 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_line_height(float dist, float pa, float ra)
{
	int	line_height;

	dist *= cosf(normalize_radians(pa - ra));
	line_height = (TILE_SIZE * WINDOW_HEIGHT) / dist;
	return (line_height);
}

void	init_tile(t_var *data, t_ray *ray, t_tex *tile)
{
	tile->line_h = get_line_height(ray->dis_h, data->player.pa, ray->ra);
	tile->ty_step = (float) TILE_SIZE_TEXTURE / (float) tile->line_h;
	if (tile->line_h > WINDOW_HEIGHT)
	{
		tile->ty_off = (tile->line_h - WINDOW_HEIGHT) / 2.0;
		tile->line_h = WINDOW_HEIGHT;
	}
	tile->line_off = (WINDOW_HEIGHT / 2) - (tile->line_h >> 1);
	tile->ty = tile->ty_off * tile->ty_step;
	if (ray->side_h == 1)
	{
		tile->tx = (int)(ray->rx) % TILE_SIZE;
		if (ray->ra > PI)
			tile->tx = TILE_SIZE - tile->tx - 1;
		if (ray->ra <= PI && ray->hit_type_h != WALL)
			tile->tx = TILE_SIZE - tile->tx - 1;
	}
	else
	{
		tile->tx = (int)(ray->ry) % TILE_SIZE;
		if (ray->ra > PI / 2 && ray->ra < 1.5 * PI && ray->hit_type_h == WALL)
			tile->tx = TILE_SIZE - tile->tx - 1;
	}
	tile->tx = tile->tx * TILE_SIZE_TEXTURE / TILE_SIZE;
}

void	draw_3d(t_var *data, t_ray *ray)
{
	t_tex	tile;

	tile = (t_tex){0};
	init_tile(data, ray, &tile);
	draw_3d_helper(data, ray, &tile);
}

void	draw_3d_helper(t_var *data, t_ray *ray, t_tex *tile)
{
	t_img	*tex;
	int		color;
	int		y;
	int		x;

	tex = get_texture(data, ray);
	x = ray->r * STRIP_WIDTH;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		if (y < tile->line_off)
			color = data->map.textures[CEILING].color;
		else if (y < tile->line_h + tile->line_off)
		{
			color = get_color((int)tile->tx, (int)tile->ty, tex);
			if (color == -1)
				color = 0xFFFFFF;
			tile->ty += tile->ty_step;
		}
		else
			color = data->map.textures[FLOOR].color;
		draw_wall_strip(&data->image, x, y, color);
		y++;
	}
}

void	draw_wall_strip(t_img *img, int x, int y, int color)
{
	int	w;

	w = 0;
	while (w < STRIP_WIDTH)
	{
		if (x + w >= WINDOW_WIDTH)
			return ;
		my_mlx_pixel_put(img, x + w, y, color);
		w++;
	}
}
