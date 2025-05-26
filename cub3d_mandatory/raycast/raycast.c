/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:53:45 by dfasius           #+#    #+#             */
/*   Updated: 2025/05/26 13:53:46 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cast_rays(t_ray *ray)
{
	if (ray->dis_h > ray->dis_v)
	{
		ray->side_h = ray->side_v;
		ray->hit_type_h = ray->hit_type_v;
		ray->dis_h = ray->dis_v;
		ray->rx = ray->vx;
		ray->ry = ray->vy;
	}
}

void	draw_rays(t_var *data)
{
	t_ray	ray;

	ray = (t_ray){0};
	ray.ra = normalize_radians(data->player.pa - (PI / 6));
	ray.r = 0;
	while (ray.r < NUM_RAYS)
	{
		ray.side_v = 0;
		ray.side_h = 1;
		ray.hit_type_v = EMPTY_SPACE;
		ray.hit_type_h = EMPTY_SPACE;
		cast_vertical(data, &ray);
		cast_horizontal(data, &ray);
		data->zbuffer[ray.r] = fmin(ray.dis_h, ray.dis_v);
		cast_rays(&ray);
		draw_3d(data, &ray);
		ray.ra += (PI / 3) / NUM_RAYS;
		ray.ra = normalize_radians(ray.ra);
		ray.r++;
	}
}
