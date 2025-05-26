/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:53:59 by dfasius           #+#    #+#             */
/*   Updated: 2025/05/26 13:54:00 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_textures(t_var *data)
{
	t_id	*tex;
	int		i;

	i = 0;
	tex = data->map.textures;
	while (i <= WEST)
	{
		extract_img(data->mlx, &tex[i].attr, tex[i].filename, data);
		i++;
	}
	while (i <= CEILING)
	{
		extract_rgb(&tex[i].color, tex[i].filename, data);
		i++;
	}
}

int	extract_img(void *mlx, t_img *attr, char *filename, t_var *data)
{
	attr->img = mlx_xpm_file_to_image(mlx, filename,
			&attr->width, &attr->height);
	if (!attr->img)
		handle_error("mlx_xpm_file_to_image failed",
			NULL, &data->map, data);
	attr->addr = mlx_get_data_addr(attr->img,
			&attr->bits_per_pixel, &attr->line_length, &attr->endian);
	if (!attr->addr)
		handle_error("mlx_get_data_addr failed", NULL, &data->map, data);
	return (0);
}

int	extract_rgb(int *color, char *rgb, t_var *data)
{
	char	**colors;

	colors = ft_split(rgb, ',');
	if (!colors)
		handle_error("malloc failed", NULL, &data->map, data);
	*color = (ft_atoi(colors[0]) << 16)
		| (ft_atoi(colors[1]) << 8) | ft_atoi(colors[2]);
	ft_free_2d(&colors);
	return (0);
}

t_img	*get_texture(t_var *data, t_ray *ray)
{
	if (ray->side_h == 0)
	{
		if (ray->rx > data->player.px)
			return (&data->map.textures[EAST].attr);
		return (&data->map.textures[WEST].attr);
	}
	else
	{
		if (ray->ry > data->player.py)
			return (&data->map.textures[SOUTH].attr);
		return (&data->map.textures[NORTH].attr);
	}
}

int	get_color(int x, int y, t_img *tex)
{
	int	pixel_index;
	int	color;

	pixel_index = y * tex->line_length + x * (tex->bits_per_pixel / 8);
	color = *(int *)(tex->addr + pixel_index);
	if ((color & 0x00FFFFFF) == 0x000000)
		return (-1);
	return (color);
}
