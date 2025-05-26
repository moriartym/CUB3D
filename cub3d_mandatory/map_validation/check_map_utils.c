/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:52:47 by dfasius           #+#    #+#             */
/*   Updated: 2025/05/26 13:52:48 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	validate_player(t_map *map, int player)
{
	if (player == 0)
		handle_error("There is no player's start position", NULL, map, NULL);
	if (player > 1)
		handle_error("There is mutiple player's start position",
			NULL, map, NULL);
}

void	find_max_row_length(t_map *map)
{
	int	i;
	int	len;

	i = 0;
	map->max_length = 0;
	while (map->arr[i])
	{
		len = ft_strlen(map->arr[i]);
		if (len > map->max_length)
			map->max_length = len;
		i++;
	}
}

void	adjust_map_length(char **map_row, t_map *map)
{
	int		len;
	char	*new_row;

	len = ft_strlen(*map_row);
	if (len == map->max_length)
		return ;
	new_row = malloc (sizeof(char *) * map->max_length + 1);
	if (!new_row)
		handle_error("malloc error", NULL, map, NULL);
	ft_memcpy(new_row, *map_row, len);
	free(*map_row);
	if (new_row[len - 1] == '\n')
		len--;
	while (len < map->max_length - 1)
	{
		new_row[len] = 'X';
		len++;
	}
	new_row[len++] = '\n';
	new_row[len] = '\0';
	*map_row = new_row;
}

void	replace_space(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->arr[i])
	{
		j = 0;
		while (map->arr[i][j])
		{
			if (map->arr[i][j] == ' ')
				map->arr[i][j] = 'X';
			j++;
		}
		adjust_map_length(&map->arr[i], map);
		i++;
	}
}
