/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okosiako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 19:24:09 by okosiako          #+#    #+#             */
/*   Updated: 2016/12/05 18:13:46 by okosiako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *nbr)
{
	long			result;
	unsigned int	index;
	int				neg;

	result = 0;
	index = 0;
	neg = 0;
	while (nbr[index] <= ' ')
		index++;
	if (nbr[index] == '+')
		index++;
	else if (nbr[index] == '-')
	{
		index++;
		neg = 1;
	}
	while (nbr[index] >= '0' && nbr[index] <= '9')
	{
		result *= 10;
		result += (nbr[index++] - '0');
	}
	if (neg)
		result *= -1;
	return ((int)result);
}
