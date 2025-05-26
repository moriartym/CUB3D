/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:52:22 by dfasius           #+#    #+#             */
/*   Updated: 2025/05/26 13:52:24 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	safe_close(int *fd)
{
	if (*fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}

void	free_single_img(void **img_ptr, t_var *data)
{
	if (img_ptr && *img_ptr)
	{
		mlx_destroy_image(data->mlx, *img_ptr);
		*img_ptr = NULL;
	}
}
