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

//void delete_map(t_region *region, t_zone *zone)
//{
//    size_t type;
//    t_region *current;
//    t_region *previous;
//
//    type = ft_get_type_region(zone->length);
//    current = base.tabList[type - 1];
//    while (current) {
//        if (current == t_region)
//        {
//            if (!previous)
//                base.tabList[type - 1] = current->next;
//            else
//                previous->next = current->next;
//            if (type == TINY_TYPE)
//                munmap(region, TINY_LENGTH);
//            else if (type == SMALL_TYPE)
//                munmap(region, SMALL_LENGTH);
//            else
//                munmap(region, current.totalLength);
//        }
//        previous = current;
//        curent = curent->next
//    }
//}

void    defrag(t_region *region, size_t regionType)
{
    t_zone  *current;
    t_zone  *next;
    size_t zone_header;

    current = region->zone;
    if (regionType == TINY_TYPE)
        zone_header = (sizeof(t_zone) + (TINY_QUANTUM_SIZE - (sizeof(t_zone) % TINY_QUANTUM_SIZE)));
    else if (regionType == SMALL_TYPE)
        zone_header = (sizeof(t_zone) + (SMALL_QUANTUM_SIZE - (sizeof(t_zone) % SMALL_QUANTUM_SIZE)));
    else
        zone_header = (sizeof(t_zone) + (LARGE_QUANTUM_SIZE - (sizeof(t_zone) % LARGE_QUANTUM_SIZE)));
    while (current)
    {
        if (current->free == TRUE)
        {
            next = current->next;
            while (next && next->free == TRUE)
            {
                current->length += (next->length + zone_header);
                current->next = next->next;
                next = next->next;
            }
        }
        current = current->next;
    }
}

void	free(void * address)
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
    region->length += zone->length;
    //defrag(region, ft_get_type_region(zone->length));
    //if (get_list_region_length(region) == 0)
        //delete_map(region);
}