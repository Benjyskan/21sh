/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 14:31:37 by penzo             #+#    #+#             */
/*   Updated: 2018/11/18 15:54:51 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_skipblank(const char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	return (i);
}

static int		ft_chartoint(const char *str)
{
	int		res;
	int		i;
	int		multi;

	i = 0;
	res = 0;
	multi = 1;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	i--;
	while (i > -1)
	{
		res += (str[i] - 48) * multi;
		multi = multi * 10;
		i--;
	}
	return (res);
}

int				ft_atoi(const char *str)
{
	int		i;
	int		modifier;

	i = 0;
	modifier = 1;
	str = &str[ft_skipblank(str)];
	if (!((str[i] == '+' && str[i + 1] >= '0' && str[i + 1] <= '9')
				|| (str[i] == '-' && str[i + 1] >= '0' && str[i + 1] <= '9')
				|| (str[i] >= '0' && str[i] <= '9')))
		return (0);
	if (str[i] == '-')
		modifier = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	return (modifier * ft_chartoint(&str[i]));
}
