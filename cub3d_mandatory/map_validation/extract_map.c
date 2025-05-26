/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:53:05 by dfasius           #+#    #+#             */
/*   Updated: 2025/05/26 13:53:06 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	extract_map(t_map *map)
{
	check_map_name(map->name);
	map->open_fd = open(map->name, O_RDONLY);
	if (map->open_fd == -1)
		handle_error("Error when opening file", map->name, map, NULL);
	extract_elements(map);
	extract_content(map);
	check_map(map);
	map->width = map->max_length - 1;
}

void	check_map_name(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	i -= 4;
	if (ft_strncmp(file + i, ".cub", 4) != 0)
		handle_error("File must be in .cub", NULL, NULL, NULL);
}
