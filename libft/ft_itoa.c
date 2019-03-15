/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 15:04:57 by penzo             #+#    #+#             */
/*   Updated: 2018/11/18 15:55:14 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_getnblen(int n)
{
	int		len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		len = 1;
	}
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*ft_allocate(int n)
{
	char	*str;

	if (!(str = ft_strnew(ft_getnblen(n) + 0)))
		return (NULL);
	return (str);
}

static char	*ft_intmin(void)
{
	char	*str;

	if (!(str = ft_allocate(12)))
		return (NULL);
	ft_strcpy(str, "-2147483648");
	return (str);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		i;

	if (n == -2147483648)
		return (ft_intmin());
	if (!(str = ft_allocate(n)))
		return (NULL);
	len = ft_getnblen(n);
	i = 0;
	if (n < 0)
	{
		n = -n;
		str[0] = '-';
		i = 1;
	}
	while (len > i)
	{
		str[len - 1] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (str);
}
