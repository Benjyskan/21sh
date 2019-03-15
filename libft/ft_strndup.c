/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 19:46:13 by penzo             #+#    #+#             */
/*   Updated: 2018/11/22 11:13:34 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strndup(const char *s1, size_t n)
{
	char	*dest;
	int		i;
	int		length;

	length = (n < ft_strlen(s1) ? n : ft_strlen(s1));
	if (!(dest = ((char*)malloc(sizeof(char) * (length + 1)))))
		return (dest);
	i = 0;
	while (s1[i] && n > 0)
	{
		dest[i] = s1[i];
		i++;
		n--;
	}
	dest[i] = 0;
	return (dest);
}
