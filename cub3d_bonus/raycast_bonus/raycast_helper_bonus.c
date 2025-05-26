/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_helper_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:48:22 by dfasius           #+#    #+#             */
/*   Updated: 2025/05/26 13:48:23 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

bool	is_wall(t_var *data, int x, int y, int notWall)
{
	char	c;

	if (notWall)
		return (false);
	if (y < 0 || y >= data->big_height || data->big_map[y] == NULL)
		return (false);
	if (x < 0 || x >= (int)ft_strlen(data->big_map[y]))
		return (false);
	c = data->big_map[y][x];
	return (c == WALL || c == DOORV_CLOSE || c == DOORV_OPEN
		|| c == DOORH_CLOSE || c == DOORH_OPEN);
}

void	cast_vertical(t_var *data, t_ray *ray)
{
	ray->dis_v = 100000;
	ray->dof = 0;
	ray->tan = -tanf(ray->ra);
	ray->cur_tile = 0;
	if (cosf(ray->ra) > 0.001)
	{
		ray->rx = ((int)(data->player.px) / TILE_SIZE_BIG)
			* TILE_SIZE_BIG + TILE_SIZE_BIG;
		ray->xo = TILE_SIZE_BIG;
	}
	else if (cosf(ray->ra) < -0.001)
	{
		ray->rx = ((int)(data->player.px) / TILE_SIZE_BIG)
			* TILE_SIZE_BIG - 0.0001;
		ray->xo = -TILE_SIZE_BIG;
	}
	else
	{
		ray->rx = data->player.px;
		ray->ry = data->player.py;
		ray->dof = data->big_width;
	}
	ray->ry = (data->player.px - ray->rx) * ray->tan + data->player.py;
	ray->yo = -ray->xo * ray->tan;
	vertical_dof(data, ray);
}

void	vertical_dof(t_var *data, t_ray *ray)
{
	while (ray->dof < data->big_width)
	{
		ray->mx = (int)(ray->rx) / TILE_SIZE_BIG;
		ray->my = (int)(ray->ry) / TILE_SIZE_BIG;
		if (is_wall(data, ray->mx, ray->my, ray->cur_tile))
		{
			ray->hit_type_v = data->big_map[ray->my][ray->mx];
			if (ray->hit_type_v == DOORH_CLOSE || ray->hit_type_v == DOORH_OPEN)
				ray->hit_type_v = 'S';
			ray->dof = data->big_width;
			ray->vx = ray->rx;
			ray->vy = ray->ry;
			ray->dis_v = sqrt(pow(ray->rx - data->player.px, 2)
					+ pow(ray->ry - data->player.py, 2));
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->dof += 1;
		}
		ray->cur_tile = 0;
	}
}

void	cast_horizontal(t_var *data, t_ray *ray)
{
	ray->dis_h = 100000;
	ray->dof = 0;
	ray->tan = 1 / ray->tan;
	ray->cur_tile = 0;
	if (sinf(ray->ra) < -0.001)
	{
		ray->ry = ((int)(data->player.py) / TILE_SIZE_BIG)
			* TILE_SIZE_BIG - 0.0001;
		ray->yo = -TILE_SIZE_BIG;
	}
	else if (sinf(ray->ra) > 0.001)
	{
		ray->ry = ((int)(data->player.py) / TILE_SIZE_BIG)
			* TILE_SIZE_BIG + TILE_SIZE_BIG;
		ray->yo = TILE_SIZE_BIG;
	}
	else
	{
		ray->rx = data->player.px;
		ray->ry = data->player.py;
		ray->dof = data->big_height;
	}
	ray->rx = (data->player.py - ray->ry) * ray->tan + data->player.px;
	ray->xo = -ray->yo * ray->tan;
	horizontal_dof(data, ray);
}

void	horizontal_dof(t_var *data, t_ray *ray)
{
	while (ray->dof < data->big_height)
	{
		ray->mx = (int)(ray->rx) / TILE_SIZE_BIG;
		ray->my = (int)(ray->ry) / TILE_SIZE_BIG;
		if (is_wall(data, ray->mx, ray->my, ray->cur_tile))
		{
			ray->hit_type_h = data->big_map[ray->my][ray->mx];
			if (ray->hit_type_h == DOORV_CLOSE || ray->hit_type_h == DOORV_OPEN)
				ray->hit_type_h = 'S';
			ray->dof = data->big_height;
			ray->dis_h = sqrt(pow(ray->rx - data->player.px, 2)
					+ pow(ray->ry - data->player.py, 2));
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->dof += 1;
		}
		ray->cur_tile = 0;
	}
}
