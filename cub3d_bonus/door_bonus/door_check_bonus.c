/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_check_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:42:05 by dfasius           #+#    #+#             */
/*   Updated: 2025/05/26 13:42:07 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

bool	is_door(char c)
{
	if (c && (c == DOORH_CLOSE || c == DOORV_CLOSE
			|| c == DOORH_OPEN || c == DOORV_OPEN
			|| c == DOOR_SPACE))
		return (true);
	return (false);
}

bool	check_door_dof(t_var *data, t_ray *ray, int *found_x, int *found_y)
{
	int	px;
	int	py;

	ray->dof = 0;
	px = (int)(data->player.px / TILE_SIZE_BIG);
	py = (int)(data->player.py / TILE_SIZE_BIG);
	while (ray->dof < 4)
	{
		ray->rx += ray->vx * TILE_SIZE_BIG;
		ray->ry += ray->vy * TILE_SIZE_BIG;
		update_mxy_from_rxy(ray);
		if (ray->my >= 0 && ray->my < data->big_height
			&& ray->mx >= 0 && ray->mx < data->big_width)
		{
			ray->cur_tile = data->big_map[ray->my][ray->mx];
			if (is_door(ray->cur_tile) && data->big_map[py][px] != DOOR_SPACE)
			{
				*found_x = ray->mx / 4;
				*found_y = ray->my / 4;
				return (true);
			}
		}
		ray->dof++;
	}
	return (false);
}

void	check_for_door_in_fov(t_var *data, int *found_x, int *found_y)
{
	t_ray	ray;
	int		px;
	int		py;

	ray = (t_ray){0};
	ray.ori_x = data->player.px;
	ray.ori_y = data->player.py;
	ray.ra = data->player.pa - (FOV / 2);
	ray.angle_step = FOV / DOOR_RAY;
	ray.r = 0;
	px = (int)(data->player.px / TILE_SIZE);
	py = (int)(data->player.py / TILE_SIZE);
	while (ray.r < DOOR_RAY)
	{
		ray.rx = ray.ori_x;
		ray.ry = ray.ori_y;
		ray.ra = data->player.pa - (FOV / 2) + ray.r * ray.angle_step;
		ray.vx = cosf(ray.ra);
		ray.vy = sinf(ray.ra);
		if (check_door_dof(data, &ray, found_x, found_y))
			return ;
		ray.r++;
	}
	*found_x = px + (int)roundf(cosf(data->player.pa));
	*found_y = py + (int)roundf(sinf(data->player.pa));
}

void	update_mxy_from_rxy(t_ray *ray)
{
	ray->mx = (int)(ray->rx / TILE_SIZE_BIG);
	ray->my = (int)(ray->ry / TILE_SIZE_BIG);
}
