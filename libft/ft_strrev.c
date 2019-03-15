/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 16:28:39 by penzo             #+#    #+#             */
/*   Updated: 2018/11/20 16:07:20 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char const *s)
{
	int		len;
	char	*res;
	int		i;

	if (!s)
		return (0);
	len = ft_strlen(s);
	if (!(res = ft_strnew(len)))
		return (0);
	i = 0;
	while (len)
	{
		res[i] = s[len - 1];
		i++;
		len--;
	}
	res[i] = 0;
	return (res);
}
