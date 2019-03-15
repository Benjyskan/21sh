/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 19:05:00 by penzo             #+#    #+#             */
/*   Updated: 2018/11/22 10:47:58 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	int		i;

	if (len == 0)
		return (b);
	i = 0;
	while (i < (int)len)
	{
		((unsigned char*)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
