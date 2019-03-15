/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 17:24:36 by penzo             #+#    #+#             */
/*   Updated: 2018/11/22 11:38:12 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	if (!(new = malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		new->content = NULL;
		new->content_size = 0;
	}
	else
	{
		if (!(new->content = malloc(sizeof(content) * content_size)))
			return (NULL);
		ft_memcpy(new->content, content, content_size);
		if (!(new->content_size = (size_t)malloc(sizeof(size_t))))
			return (NULL);
		new->content_size = content_size;
	}
	new->next = NULL;
	return (new);
}
