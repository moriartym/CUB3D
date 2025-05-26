/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:44:31 by dfasius           #+#    #+#             */
/*   Updated: 2025/05/26 13:44:33 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	free_state_images(t_var *data)
{
	free_single_img((void **)&data->state.win.img, data);
	free_single_img((void **)&data->state.lose.img, data);
}

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
