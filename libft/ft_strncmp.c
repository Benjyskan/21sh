/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 16:16:23 by penzo             #+#    #+#             */
/*   Updated: 2018/11/18 11:08:09 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		i;

	if (s1[0] == 0 && n > 0)
		return (-(unsigned char)s2[0]);
	if (s2[0] == 0 && n > 0)
		return ((unsigned char)s1[0]);
	i = 0;
	while (s1[i] && s2[i] && n > 0)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
		n--;
	}
	if (!n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
