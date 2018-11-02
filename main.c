/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 12:04:00 by hmadad            #+#    #+#             */
/*   Updated: 2018/08/31 15:11:51 by hmadad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "includes/ft_malloc.h"

int		main(int ac, char **av) {
    char *str2[1024];
    int  i;

    (void)ac;
    if (ac != 2)
    {
        printf("Need number of allocation (ex: ./test 3)\n");
        return 0;
    }
    i = atoi(av[1]);
    while (i-- != 0)
        str2[i] = (char *)malloc(1024);

    return (0);
}