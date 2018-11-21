/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 12:04:00 by hmadad            #+#    #+#             */
/*   Updated: 2018/11/15 14:55:09 by hmadad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_malloc.h"

int		main(int ac, char **av)
{
	char	*str2;
	int		i;

	(void)ac;
	(void)str2;
	if (ac != 2)
	{
		ft_putstr("Need number of allocation (ex: ./test 3)\n");
		return (0);
	}
	i = atoi(av[1]);
	while (i > 0)
	{
		str2 = (char *)malloc(1024);
		str2[0] = 42;
		i--;
	}
	ft_show_alloc_mem();
	return (0);
}
