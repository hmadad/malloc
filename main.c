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
    char *str2[1000];
    int  i;

    (void)ac;
    if (ac != 2)
    {
        printf("Need number of allocation (ex: ./test 3)\n");
        return 0;
    }
    i = atoi(av[1]);
    str = (char *)malloc(200);
    while (i-- != 0)
        str2[i] = (char *)malloc(900);
    free(str2[12]);
    free(str2[13]);
    free(str2[14]);
    free(str2[15]);
    free(str2[16]);
    free(str2[120]);
    str2[0] = realloc(str2[127], 500);
    str2[0] = realloc(str2[128], 500);
    str2[0] = realloc(str2[129], 500);
    str2[0] = realloc(str2[2], 500);
    str2[0] = realloc(str2[997], 500);
    str2[0] = realloc(str2[998], 500);
    str2[0] = realloc(str2[0], 500);
    str2[0] = realloc(str2[0], 500);
    str2[0] = realloc(str2[0], 500);
    str2[0] = realloc(str2[0], 500);
    ft_show_alloc_mem();

    return (0);
}