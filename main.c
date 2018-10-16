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
    char *str;
    char *str2;
    //char *str3;
    int  i;

    (void)ac;
    if (ac != 2)
    {
        printf("Need number of allocation (ex: ./test 3)\n");
        return 0;
    }
    i = atoi(av[1]);
    str = (char *)ft_malloc(200);
    while (i-- != 0)
        str2 = (char *)ft_malloc(1);
    ft_show_alloc_mem();
    str2 = ft_realloc(str2, 16);
    ft_show_alloc_mem();

    str2 = ft_realloc(str2, 1);
    ft_show_alloc_mem();
    str2 = ft_realloc(str2, 16);
    ft_show_alloc_mem();
    str2 = ft_realloc(str2, 1);
    str2 = ft_realloc(str2, 16);
    str2 = ft_realloc(str2, 1);
    str2 = ft_realloc(str2, 16);
    str2 = ft_realloc(str2, 1);
    str2 = ft_realloc(str2, 16);
    ft_show_alloc_mem();

    return (0);
}