/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 17:26:51 by penzo             #+#    #+#             */
/*   Updated: 2018/11/26 10:22:26 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		len;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(res = ft_strnew(len + 1)))
		return (NULL);
	ft_strncpy(res, s1, len);
	i = ft_strlen(s1);
	j = 0;
	while (i < len)
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = 0;
	return (res);
}
