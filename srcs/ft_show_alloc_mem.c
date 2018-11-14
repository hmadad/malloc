/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_alloc_mem.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 12:04:00 by hmadad            #+#    #+#             */
/*   Updated: 2018/08/31 15:11:51 by hmadad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

t_base g_base;

void    ft_print_zone(t_zone *zone)
{
    while (zone)
    {

        if (zone->free == FALSE)
        {
            write(1, "0x", 2);
            ft_putnbr_base((size_t)zone->content, 16);
            ft_putstr(" - 0x");
            ft_putnbr_base((size_t)(zone->content + zone->length), 16);
            ft_putstr(" : ");
            ft_putnbr_base((size_t)zone->length, 10);
            ft_putstr(" octets\n");
        }
        else
        {
            write(1, "0x", 2);
            ft_putnbr_base((size_t)zone->content, 16);
            ft_putstr(" : ");
            ft_putnbr_base((size_t)zone->length, 10);
            ft_putstr(" octets - FREE\n");
        }
        zone = zone->next;
    }
}

void    ft_print_region(t_region *region, size_t regionType)
{
    size_t  zone_header;

    while (region)
    {
        if (regionType == TINY_TYPE)
        {
            zone_header = (sizeof(t_zone) + (TINY_QUANTUM_SIZE - (sizeof(t_zone) % TINY_QUANTUM_SIZE)));
            ft_putstr("TINY : 0x");
        }
        if (regionType == SMALL_TYPE)
        {
            zone_header = (sizeof(t_zone) + (SMALL_QUANTUM_SIZE - (sizeof(t_zone) % SMALL_QUANTUM_SIZE)));
            ft_putstr("SMALL : 0x");
        }
        if (regionType == LARGE_TYPE)
        {
            zone_header = (sizeof(t_zone) + (LARGE_QUANTUM_SIZE - (sizeof(t_zone) % LARGE_QUANTUM_SIZE)));
            ft_putstr("LARGE : 0x");
        }
        ft_putnbr_base((size_t)region, 16);
        write(1, "\n", 1);
        if (region->zone)
            ft_print_zone(region->zone);
        region = region->next;
    }
}

void    ft_show_alloc_mem()
{
    if (get_list_region_length(TINY_TYPE) != 0)
        ft_print_region(g_base.tabList[0], TINY_TYPE);
    if (get_list_region_length(SMALL_TYPE) != 0)
        ft_print_region(g_base.tabList[1], SMALL_TYPE);
    if (get_list_region_length(LARGE_TYPE) != 0)
        ft_print_region(g_base.tabList[2], LARGE_TYPE);
}