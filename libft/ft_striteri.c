/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 12:24:29 by penzo             #+#    #+#             */
/*   Updated: 2018/11/18 17:38:16 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int				i;
	unsigned int	index;

	if (!s || !f)
		return ;
	i = 0;
	index = 0;
	while (s[i])
	{
		f(index, &s[i]);
		i++;
		index++;
	}
	return ;
}
