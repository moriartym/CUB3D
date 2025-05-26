/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_helper_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:47:22 by dfasius           #+#    #+#             */
/*   Updated: 2025/05/26 13:47:23 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	mouse_state(t_var *data)
{
	if (!data->mouse_state)
		data->mouse_state = 1;
	else
	{
		data->last_mouse_x = -1;
		data->mouse_state = 0;
	}
}
