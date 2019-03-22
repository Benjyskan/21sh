/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_nultab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 15:38:35 by penzo             #+#    #+#             */
/*   Updated: 2019/03/22 15:31:07 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	**ft_dup_nultab(char **tab)
{
	char	**new_tab;
	int		tab_len;
	int		i;

	if (!tab || !*tab)
		return (NULL);
	tab_len = get_ntab_len(tab);
	if (!(new_tab = (char**)malloc((sizeof(char*) * (tab_len + 1)))))
		return (NULL);
	i = -1;
	while (++i < tab_len)
	{
		if (!(new_tab[i] = ft_strdup(tab[i])))
		{
			ft_free_nultab(new_tab);
			return (NULL);
		}
	}
	new_tab[i] = NULL;
	return (new_tab);
}
