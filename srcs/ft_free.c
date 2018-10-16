/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 12:04:00 by hmadad            #+#    #+#             */
/*   Updated: 2018/08/31 15:11:51 by hmadad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

t_base base;



void ft_reset_str(char *str)
{
    int i;

    i = 0;
    while (i < 8)
    {
        str[i] = 0;
        i++;
    }
}

void	ft_free(void * address)
{
    t_region * region;
    t_zone * zone;
    if (!address)
        return;
    region = ft_find_region(address);
    if (!region)
        return;
    zone = ft_find_zone(address, region);
    if (!zone)
        return;
    zone->free = TRUE;
    ft_reset_str(zone->content);
}