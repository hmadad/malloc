/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 12:04:00 by hmadad            #+#    #+#             */
/*   Updated: 2018/11/15 14:02:17 by hmadad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include "includes/ft_malloc.h"

int		main(int ac, char **av)
{
	char	*str2[5000];
	int		i;

	(void)ac;
	if (ac != 2)
	{
		ft_putstr("Need number of allocation (ex: ./test 3)\n");
		return (0);
	}
	i = atoi(av[1]);
	while (i-- > 0)
		str2[i] = (char *)malloc(900);
	ft_show_alloc_mem();
	i = atoi(av[1]);
	ft_putstr("========================\n");
	while (i-- > 0)
		free(str2[i]);
	ft_show_alloc_mem();
	return (0);
}
