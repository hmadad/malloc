/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_region_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 12:04:00 by hmadad            #+#    #+#             */
/*   Updated: 2018/11/02 10:57:24 by hmadad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

t_base base;

int     get_list_region_length(size_t region) {
    t_region    *current;
    size_t      i;

    i = 0;
    current = base.tabList[region - 1];
    while (current)
    {
        i++;
        current = current->next;
    }
    return i;
}

void     *ft_search_region_place(size_t region, size_t len)
{
    t_region    *current;
    size_t      zone_header;
    size_t      length_with_quantum;

    current = base.tabList[region - 1];
    while (current)
    {
        if (region == TINY_TYPE)
        {
            zone_header = (sizeof(t_zone) + (TINY_QUANTUM_SIZE - (sizeof(t_zone) % TINY_QUANTUM_SIZE)));
            length_with_quantum = (len + (TINY_QUANTUM_SIZE - (len % TINY_QUANTUM_SIZE)));
            if (current->length > (zone_header + length_with_quantum))
                return current;
        }
        else if (region == SMALL_TYPE)
        {
            zone_header = (sizeof(t_zone) + (SMALL_QUANTUM_SIZE - (sizeof(t_zone) % SMALL_QUANTUM_SIZE)));
            length_with_quantum = (len + (SMALL_QUANTUM_SIZE - (len % SMALL_QUANTUM_SIZE)));
            if (current->length > zone_header + length_with_quantum)
                return current;
        }
        else
        {
            zone_header = (sizeof(t_zone) + (LARGE_QUANTUM_SIZE - (sizeof(t_zone) % LARGE_QUANTUM_SIZE)));
            length_with_quantum = (len + (LARGE_QUANTUM_SIZE - (len % LARGE_QUANTUM_SIZE)));
            if (current->length > zone_header + length_with_quantum)
                return current;
        }
        current = current->next;
    }
    return NULL;
}

void    *get_last_list_region(size_t region) {
    t_region    *current;

    current = base.tabList[region - 1];
    while (current && current->next)
    {
        current = current->next;
    }
    return current;
}

void    *ft_create_new_list_region(size_t len, t_region *address)
{
    t_region    *lastElement;
    size_t      header_length;
    size_t      zone_header;
    size_t      length_with_quantum;
    t_zone      *zone;

    address->next = NULL;
    address->type = ft_get_type_region(len);
    if (address->type == TINY_TYPE)
    {
        header_length = (sizeof(t_region) + (TINY_QUANTUM_SIZE - (sizeof(t_region) % TINY_QUANTUM_SIZE)));
        zone_header = (sizeof(t_zone) + (TINY_QUANTUM_SIZE - (sizeof(t_zone) % TINY_QUANTUM_SIZE)));
        length_with_quantum = (len + (TINY_QUANTUM_SIZE - (len % TINY_QUANTUM_SIZE)));
        address->length = TINY_LENGTH - header_length;
        address->length -= zone_header;
        address->length -= length_with_quantum;
        address->zone = (void *)address + header_length;
    }
    else if (address->type == SMALL_TYPE)
    {
        header_length = (sizeof(t_region) + (SMALL_QUANTUM_SIZE - (sizeof(t_region) % SMALL_QUANTUM_SIZE)));
        zone_header = (sizeof(t_zone) + (SMALL_QUANTUM_SIZE - (sizeof(t_zone) % SMALL_QUANTUM_SIZE)));
        length_with_quantum = (len + (SMALL_QUANTUM_SIZE - (len % SMALL_QUANTUM_SIZE)));
        address->length = SMALL_LENGTH - header_length;
        address->length -= zone_header;
        address->length -= length_with_quantum;
        address->zone = (void *)address + header_length;
    }
    else
    {
        header_length = (sizeof(t_region) + (LARGE_QUANTUM_SIZE - (sizeof(t_region) % LARGE_QUANTUM_SIZE)));
        zone_header = (sizeof(t_zone) + (LARGE_QUANTUM_SIZE - (sizeof(t_zone) % LARGE_QUANTUM_SIZE)));
        length_with_quantum = (len + (LARGE_QUANTUM_SIZE - (len % LARGE_QUANTUM_SIZE)));
        address->length = (len + (PAGESIZE - (len % PAGESIZE))) * 100 - header_length;
        address->length -= zone_header;
        address->length -= length_with_quantum;
        address->zone = (void *)address + header_length;
    }
    lastElement = get_last_list_region(address->type);
    if (!lastElement)
        base.tabList[address->type - 1] = address;
    else
        lastElement->next = address;
    zone = address->zone;
    zone->length = address->length;
    zone->free = TRUE;
    zone->next = NULL;
    return ft_create_new_zone_list((t_zone *)address->zone, length_with_quantum, zone_header);
}
