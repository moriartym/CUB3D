/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisdigit.c                                       :+:      :+:    :+:*/
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:52:25 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/19 19:22:40 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strisdigit(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
/*
#include <stdio.h>
#include <ctype.h>
int	main(void)
{
	printf("%d\n",ft_isdigit('a'));
	printf("%d\n", isdigit('a'));
	printf("%d\n",ft_isdigit('0'));
        printf("%d\n", isdigit('9'));

}
*/
