/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:53:54 by dfasius           #+#    #+#             */
/*   Updated: 2025/05/26 13:53:55 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_wall(t_var *data, int x, int y)
{
	char	c;

	if (y < 0 || y >= data->map.height || data->map.arr[y] == NULL)
		return (false);
	if (x < 0 || x >= (int)ft_strlen(data->map.arr[y]))
		return (false);
	c = data->map.arr[y][x];
	return (c == WALL);
}

void	cast_vertical(t_var *data, t_ray *ray)
{
	ray->dis_v = 100000;
	ray->dof = 0;
	ray->tan = -tanf(ray->ra);
	if (cosf(ray->ra) > 0.001)
	{
		ray->rx = ((int)(data->player.px) / TILE_SIZE)
			* TILE_SIZE + TILE_SIZE;
		ray->xo = TILE_SIZE;
	}
	else if (cosf(ray->ra) < -0.001)
	{
		ray->rx = ((int)(data->player.px) / TILE_SIZE)
			* TILE_SIZE - 0.0001;
		ray->xo = -TILE_SIZE;
	}
	else
	{
		ray->rx = data->player.px;
		ray->ry = data->player.py;
		ray->dof = data->map.width;
	}
	ray->ry = (data->player.px - ray->rx) * ray->tan + data->player.py;
	ray->yo = -ray->xo * ray->tan;
	vertical_dof(data, ray);
}

void	vertical_dof(t_var *data, t_ray *ray)
{
	while (ray->dof < data->map.width)
	{
		ray->mx = (int)(ray->rx) / TILE_SIZE;
		ray->my = (int)(ray->ry) / TILE_SIZE;
		if (is_wall(data, ray->mx, ray->my))
		{
			ray->hit_type_v = data->map.arr[ray->my][ray->mx];
			ray->dof = data->map.width;
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
	}
}

void	cast_horizontal(t_var *data, t_ray *ray)
{
	ray->dis_h = 100000;
	ray->dof = 0;
	ray->tan = 1 / ray->tan;
	if (sinf(ray->ra) < -0.001)
	{
		ray->ry = ((int)(data->player.py) / TILE_SIZE)
			* TILE_SIZE - 0.0001;
		ray->yo = -TILE_SIZE;
	}
	else if (sinf(ray->ra) > 0.001)
	{
		ray->ry = ((int)(data->player.py) / TILE_SIZE)
			* TILE_SIZE + TILE_SIZE;
		ray->yo = TILE_SIZE;
	}
	else
	{
		ray->rx = data->player.px;
		ray->ry = data->player.py;
		ray->dof = data->map.height;
	}
	ray->rx = (data->player.py - ray->ry) * ray->tan + data->player.px;
	ray->xo = -ray->yo * ray->tan;
	horizontal_dof(data, ray);
}

void	horizontal_dof(t_var *data, t_ray *ray)
{
	while (ray->dof < data->map.height)
	{
		ray->mx = (int)(ray->rx) / TILE_SIZE;
		ray->my = (int)(ray->ry) / TILE_SIZE;
		if (is_wall(data, ray->mx, ray->my))
		{
			ray->hit_type_h = data->map.arr[ray->my][ray->mx];
			ray->dof = data->map.height;
			ray->dis_h = sqrt(pow(ray->rx - data->player.px, 2)
					+ pow(ray->ry - data->player.py, 2));
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->dof += 1;
		}
	}
}
