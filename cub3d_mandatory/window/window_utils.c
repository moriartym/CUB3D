/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:54:27 by dfasius           #+#    #+#             */
/*   Updated: 2025/05/26 13:54:28 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_single_image(t_var *data, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(data->mlx,
			(char *)path, &img->width, &img->height);
	if (!img->img)
		handle_error("Failed to load image",
			NULL, &data->map, data);
	img->addr = mlx_get_data_addr(img->img,
			&img->bits_per_pixel, &img->line_length, &img->endian);
	if (!img->addr)
		handle_error("Failed to get image data address",
			NULL, &data->map, data);
}

void	create_image_buffer(t_var *data)
{
	data->image.img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->image.img)
		handle_error("Failed to create image", NULL, &data->map, data);
	data->image.addr = mlx_get_data_addr(data->image.img,
			&data->image.bits_per_pixel,
			&data->image.line_length,
			&data->image.endian);
	if (!data->image.addr)
		handle_error("Failed to get image address", NULL, &data->map, data);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
