/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 18:34:55 by penzo             #+#    #+#             */
/*   Updated: 2018/11/17 18:30:51 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;

	if (alst != NULL && del != NULL)
	{
		while ((*alst)->next)
		{
			tmp = (*alst)->next;
			ft_lstdelone(alst, del);
			(*alst) = tmp;
		}
		ft_lstdelone(alst, del);
	}
	return ;
}
