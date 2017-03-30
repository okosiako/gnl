/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okosiako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 19:00:02 by okosiako          #+#    #+#             */
/*   Updated: 2016/12/06 12:14:02 by okosiako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	long index;

	if (dst - src < 0)
	{
		index = -1;
		while (index++ < (long)len - 1)
			*(char *)(dst + index) = *(char *)(src + index);
	}
	else if (dst - src > 0)
	{
		index = len;
		while (index-- > 0)
			*(char *)(dst + index) = *(char *)(src + index);
	}
	return (dst);
}
