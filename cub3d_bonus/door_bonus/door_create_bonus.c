/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_create_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:42:27 by dfasius           #+#    #+#             */
/*   Updated: 2025/05/26 13:42:29 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	create_door(t_var *data)
{
	char	*tile;
	float	angle;
	int		found_x;
	int		found_y;

	check_for_door_in_fov(data, &found_x, &found_y);
	if (found_x >= 0 && found_x < data->map.width
		&& found_y >= 0 && found_y < data->map.height)
	{
		tile = &data->map.arr[found_y][found_x];
		if (*tile == EMPTY_SPACE)
		{
			angle = normalize_radians(data->player.pa);
			*tile = DOORV_CLOSE;
			if ((angle > PI / 4 && angle < 3 * PI / 4)
				|| (angle > 5 * PI / 4 && angle < 7 * PI / 4))
				*tile = DOORH_CLOSE;
			create_door_big_map(data, found_y, found_x);
		}
		else if (is_door(*tile))
		{
			*tile = EMPTY_SPACE;
			delete_door_big_map(data, found_y, found_x);
		}
	}
}

void	open_door(t_var *data)
{
	int		found_x;
	int		found_y;
	char	*tile;

	check_for_door_in_fov(data, &found_x, &found_y);
	if (found_x >= 0 && found_x < data->map.width
		&& found_y >= 0 && found_y < data->map.height)
	{
		tile = &data->map.arr[found_y][found_x];
		if (*tile == DOORH_CLOSE || *tile == DOORV_CLOSE)
		{
			*tile += 1;
			update_door_big_map(data, found_y, found_x);
			printf("🚪 Door Opened\n");
		}
		else if (*tile == DOORH_OPEN || *tile == DOORV_OPEN)
		{
			*tile -= 1;
			create_door_big_map(data, found_y, found_x);
			printf("🚪 Door Closed\n");
		}
	}
}
