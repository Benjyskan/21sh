/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 18:42:57 by penzo             #+#    #+#             */
/*   Updated: 2018/11/22 11:36:58 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*res;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	if (!(res = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	j = start;
	i = 0;
	while (len)
	{
		res[i] = s[j];
		i++;
		j++;
		len--;
	}
	res[i] = 0;
	return (res);
}
