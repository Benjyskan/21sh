/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 13:03:54 by penzo             #+#    #+#             */
/*   Updated: 2018/11/18 10:57:00 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int		i;

	if (n == 0)
		return (0);
	i = 0;
	while (((unsigned char*)s1)[i] == ((unsigned char*)s2)[i] && i < (int)n - 1)
		i++;
	return (((unsigned char*)s1)[i] - ((unsigned char*)s2)[i]);
}
