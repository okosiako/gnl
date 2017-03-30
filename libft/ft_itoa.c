/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okosiako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 13:48:56 by okosiako          #+#    #+#             */
/*   Updated: 2016/12/05 18:25:49 by okosiako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*convert(long nbr)
{
	char			*result;
	long			temp;
	unsigned int	i;

	i = 1;
	result = NULL;
	if (nbr < 0)
	{
		nbr = -(nbr);
		i++;
	}
	temp = nbr;
	while ((temp /= 10) != 0)
		i++;
	if (!(result = (char *)malloc(sizeof(char) * (i + 1))))
		return (0);
	result[i] = '\0';
	i--;
	while (nbr != 0)
	{
		result[i--] = (nbr % 10) + '0';
		nbr /= 10;
	}
	result[0] = (i == 0) ? '-' : result[0];
	return (result);
}

char		*ft_itoa(int nbr)
{
	char	*result;

	result = NULL;
	if (nbr == 0)
	{
		result = (char *)malloc(sizeof(char) * 2);
		result = "0";
		return (result);
	}
	return (convert((long)nbr));
}
