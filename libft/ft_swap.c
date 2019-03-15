/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 13:07:17 by penzo             #+#    #+#             */
/*   Updated: 2018/11/22 11:33:44 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_swap(void *a, void *b)
{
	void	*tmp;

	if (!(tmp = malloc(sizeof(a))))
		return ;
	ft_memcpy(tmp, b, sizeof(a));
	ft_memcpy(b, a, sizeof(a));
	ft_memcpy(a, tmp, sizeof(a));
	free(tmp);
	return ;
}
