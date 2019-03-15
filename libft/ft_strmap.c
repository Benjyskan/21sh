/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 12:24:15 by penzo             #+#    #+#             */
/*   Updated: 2018/11/17 13:19:19 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*s2;

	if (!s)
		return (NULL);
	if (!(s2 = ft_strnew(ft_strlen(s))))
		return (NULL);
	ft_strcpy(s2, s);
	i = 0;
	while (s2[i])
	{
		s2[i] = f(s2[i]);
		i++;
	}
	return (s2);
}
