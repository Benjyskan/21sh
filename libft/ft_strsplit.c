/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penzo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 17:59:49 by penzo             #+#    #+#             */
/*   Updated: 2018/11/22 11:34:15 by penzo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_count_words(char const *s, char c)
{
	int		in_word;
	int		i;
	int		count;

	in_word = 0;
	i = 0;
	count = 0;
	while (s[i])
	{
		if (in_word == 0 && s[i] != c)
		{
			in_word = 1;
			count++;
		}
		if (in_word == 1 && s[i] == c)
			in_word = 0;
		i++;
	}
	return (count);
}

static int	ft_getwordlen(char const *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static void	set_variables(int *i, int *j, int *in_word)
{
	*i = 0;
	*j = 0;
	*in_word = 0;
}

static char	**ft_filldashit(char **tab, char *ss, char c, int j)
{
	int		in_word;
	int		i;

	i = 0;
	in_word = 0;
	while (ss[i])
	{
		if (in_word == 0 && ss[i] != c)
		{
			in_word = 1;
			if (!(tab[j] = ft_strndup(&ss[i], ft_getwordlen(&ss[i], c))))
			{
				free(tab);
				return (NULL);
			}
			j++;
		}
		if (in_word == 1 && ss[i] == c)
			in_word = 0;
		i++;
	}
	tab[j] = 0;
	return (tab);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		in_word;

	if (!s)
		return (NULL);
	if (!(tab = (char**)malloc(sizeof(char**) * (ft_count_words(s, c) + 1))))
		return (NULL);
	set_variables(&i, &j, &in_word);
	ft_filldashit(tab, (char*)s, c, j);
	return (tab);
}
