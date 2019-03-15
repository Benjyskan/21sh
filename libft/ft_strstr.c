/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:54:27 by penzo             #+#    #+#             */
/*   Updated: 2018/11/15 16:13:58 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;

	if (needle[0] == 0)
		return ((char*)haystack);
	i = 0;
	while (haystack[i])
	{
		if (haystack[i] == needle[0])
			if (!(ft_strncmp(&haystack[i], needle, ft_strlen(needle))))
				return ((char*)&haystack[i]);
		i++;
	}
	return (0);
}
