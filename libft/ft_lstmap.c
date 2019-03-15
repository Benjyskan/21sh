/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 10:10:07 by penzo             #+#    #+#             */
/*   Updated: 2018/11/21 16:13:13 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*begin_new;
	t_list	*new;

	if (!lst)
		return (NULL);
	begin_new = f(ft_lstnew(lst->content, lst->content_size));
	new = begin_new;
	while (lst->next)
	{
		lst = lst->next;
		new->next = f(ft_lstnew(lst->content, lst->content_size));
		new = new->next;
	}
	return (begin_new);
}
