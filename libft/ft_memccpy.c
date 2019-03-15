/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 11:52:12 by penzo             #+#    #+#             */
/*   Updated: 2018/11/20 20:38:21 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst,
		const void *src, int c, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		((char*)dst)[i] = ((char*)src)[i];
		if (((unsigned char*)src)[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	if (!i)
		((char*)dst)[i] = ((char*)src)[i];
	return (0);
}
