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

int		main() {
    char *str;

    str = (char*)ft_malloc(2);
    if (!str)
        printf("Ya rien %p\n", str);
    else
    {
        str[0] = 'A';
        str[1] = 'A';
        str[2] = 'A';
        str[3] = 'A';
        str[4] = '\0';
    }
    printf("%p\nstr = %s\n", ft_malloc(10), str);
	return (0);
}