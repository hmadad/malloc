/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_region_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 12:04:00 by hmadad            #+#    #+#             */
/*   Updated: 2018/08/31 15:11:51 by hmadad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

t_base base;

int     get_list_region_length(size_t region) {
    t_region    *current;
    size_t      i;

    i = 0;
    current = base.tabList[region];
    while (current)
    {
        i++;
        current = current->next;
    }
    return i;
}

int     ft_search_region_place(size_t region, size_t len)
{
    t_region    *current;

    current = base.tabList[region];
    while (current)
    {
        if (region == TINY_TYPE)
        {
            if (current->length > (len + TINY_QUANTUM_SIZE))
                return &current
        }
        else if (region == SMALL_TYPE)
        {
            if (current->length > (len + SMALL_QUANTUM_SIZE))
                return &current
        }
        else
        {
            if (current->length > (len + LARGE_QUANTUM_SIZE))
                return &current
        }
        current = current->next;
    }
    return 0;
}

void    *get_last_list_region(size_t region) {
    t_region    *current;

    current = base.tabList[region];
    while (current && current->next)
    {
        current = current->next;
    }
    return current;
}

void    *ft_create_new_list_region(size_t len, t_region *address)
{
    t_region    *lastElement;

    address->next = 0;
    address->type = ft_get_type_region(len);
    if (address->type == TINY_TYPE)
    {
        address->zone = (void *)address + sizeof(t_region) + (TINY_QUANTUM_SIZE - (sizeof(t_region) % TINY_QUANTUM_SIZE));
        address->length = TINY_LENGTH - (sizeof(t_region) + (TINY_QUANTUM_SIZE - (sizeof(t_region) % TINY_QUANTUM_SIZE))) - (len + (TINY_QUANTUM_SIZE - (len % TINY_QUANTUM_SIZE)));
    }
    else if (address->type == SMALL_TYPE)
    {
        address->zone = (void *)address + sizeof(t_region) + (SMALL_QUANTUM_SIZE - (sizeof(t_region) % SMALL_QUANTUM_SIZE));
        address->length = SMALL_LENGTH - (sizeof(t_region) + (SMALL_QUANTUM_SIZE - (sizeof(t_region) % SMALL_QUANTUM_SIZE))) - (len + (SMALL_QUANTUM_SIZE - (len % SMALL_QUANTUM_SIZE)));
    }
    else
    {
        address->zone = (void *)address + sizeof(t_region) + (LARGE_QUANTUM_SIZE - (sizeof(t_region) % LARGE_QUANTUM_SIZE));
        address->length = (len + (PAGESIZE - (len % PAGESIZE)) * 100) - (sizeof(t_region) + (LARGE_QUANTUM_SIZE - (sizeof(t_region) % LARGE_QUANTUM_SIZE))) - (len + (LARGE_QUANTUM_SIZE - (len % LARGE_QUANTUM_SIZE)));
    }
    lastElement = get_last_list_region(address->type);
    if (!lastElement)
        base.tabList[address->type] = address;
    else
        lastElement->next = address;
    ft_create_new_zone_list((t_zone *)address->zone, len);
    return address->zone;
}