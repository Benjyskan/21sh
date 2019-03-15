/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 12:37:38 by penzo             #+#    #+#             */
/*   Updated: 2018/11/22 11:37:53 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int		i;
	void	*tmp;

	if (!(tmp = malloc(sizeof(void*) * len + 1)))
		return (dst);
	i = 0;
	while (i < (int)len)
	{
		((unsigned char*)tmp)[i] = ((unsigned char*)src)[i];
		i++;
	}
	i = 0;
	while (i < (int)len)
	{
		((unsigned char*)dst)[i] = ((unsigned char*)tmp)[i];
		i++;
	}
	free(tmp);
	return (dst);
}
