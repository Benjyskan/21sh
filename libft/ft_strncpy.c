/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 13:41:27 by penzo             #+#    #+#             */
/*   Updated: 2018/11/18 14:09:09 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	int		i;
	int		is_finish;

	i = 0;
	is_finish = 0;
	while (i < (int)len)
	{
		if (src[i] && !is_finish)
		{
			dst[i] = src[i];
		}
		else
		{
			dst[i] = 0;
			is_finish = 1;
		}
		i++;
	}
	return (dst);
}
