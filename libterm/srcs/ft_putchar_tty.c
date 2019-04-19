/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_tty.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 18:59:20 by pscott            #+#    #+#             */
/*   Updated: 2019/04/19 14:45:37 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libterm.h"

int		ft_putchar_tty(int c)
{
	if (write(g_dev_tty, &c, 1) == -1)
	{
		ft_putstr_fd("write error: bad file descriptor\n", 2);
		return (0);
	}
	else
		return (1);
}

int		ft_putstr_tty(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			print_line();
		else
			ft_putchar_tty(str[i]);
		i++;
	}
	return (1);
}

void	ft_endl_tty(char *str)
{
	ft_putstr_tty(str);
	print_line();
}
