/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 12:53:08 by penzo             #+#    #+#             */
/*   Updated: 2018/11/17 13:39:00 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int				i;
	unsigned int	index;
	char			*s2;

	if (!s)
		return (NULL);
	if (!(s2 = ft_strnew(ft_strlen(s))))
		return (NULL);
	ft_strcpy(s2, s);
	i = 0;
	index = 0;
	while (s2[i])
	{
		s2[i] = f(index, s2[i]);
		i++;
		index++;
	}
	return (s2);
}
