/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 16:30:01 by penzo             #+#    #+#             */
/*   Updated: 2018/11/22 10:49:27 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	int		j;

	if (needle[0] == 0)
		return ((char*)haystack);
	i = 0;
	while (haystack[i] && len > 0)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && j < (int)len)
		{
			j++;
			if (!needle[j])
				return ((char*)&haystack[i]);
		}
		i++;
		len--;
	}
	return (NULL);
}
