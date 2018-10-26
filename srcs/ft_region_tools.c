/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_region_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 12:04:00 by hmadad            #+#    #+#             */
/*   Updated: 2018/08/31 15:11:51 by hmadad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

t_base base;

int     ft_get_type_region(size_t len)
{
    if (len < TINY_LIMIT)
        return TINY_TYPE;
    else if (len < SMALL_LIMIT && len >= TINY_LIMIT)
        return SMALL_TYPE;
    else
        return LARGE_TYPE;
}

void    *ft_select_region(size_t regionType, size_t len)
{
    t_region    *region;
    void        *address;
    size_t      zone_header;
    size_t      length_with_quantum;

    address = NULL;
    region = ft_search_region_place(regionType, len);
    if (!region)
    {
        address = ft_allocate_memory(len, regionType);
        address = ft_create_new_list_region(len, (t_region *)address);
    }
    else
    {
        if (regionType == TINY_TYPE)
        {
            zone_header = (sizeof(t_zone) + (TINY_QUANTUM_SIZE - (sizeof(t_zone) % TINY_QUANTUM_SIZE)));
            length_with_quantum = (len + (TINY_QUANTUM_SIZE - (len % TINY_QUANTUM_SIZE)));
        }
        else if (regionType == SMALL_TYPE)
        {
            zone_header = (sizeof(t_zone) + (SMALL_QUANTUM_SIZE - (sizeof(t_zone) % SMALL_QUANTUM_SIZE)));
            length_with_quantum = (len + (SMALL_QUANTUM_SIZE - (len % SMALL_QUANTUM_SIZE)));
        }
        else
        {
            zone_header = (sizeof(t_zone) + (LARGE_QUANTUM_SIZE - (sizeof(t_zone) % LARGE_QUANTUM_SIZE)));
            length_with_quantum = (len + (LARGE_QUANTUM_SIZE - (len % LARGE_QUANTUM_SIZE)));
        }
        region->length = region->length - (zone_header + length_with_quantum);
        address = ft_get_free_zone(region, length_with_quantum);
        if (!address)
        {
            address = ft_allocate_memory(len, regionType);
            address = ft_create_new_list_region(len, (t_region *)address);
        }
        else
        {
            address = ft_create_new_zone_list((t_zone *)address, length_with_quantum, zone_header);
        }
    }
    return address;
}

t_region *ft_find_region(void * address)
{
    int i;
    i = 0;
    t_region *current;

    while(i < 3)
    {
        current = base.tabList[i];
        while (current)
        {
            if (address > (void *)current && address < ((void *)current + current->length))
                return current;
            current = current->next;
        }
        i++;
    }
    return NULL;
}