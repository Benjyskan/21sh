/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 12:57:42 by penzo             #+#    #+#             */
/*   Updated: 2018/11/20 13:19:02 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstappend(t_list **alst, t_list *new)
{
	t_list	*curr;

	if (new && alst)
	{
		curr = *alst;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
		return ;
	}
	return ;
}
