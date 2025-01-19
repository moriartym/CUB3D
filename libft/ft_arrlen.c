/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aputri-a <aputri-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:56:53 by aputri-a          #+#    #+#             */
/*   Updated: 2024/11/18 12:57:40 by aputri-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_arrlen(char **arr)
{
	int	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}
