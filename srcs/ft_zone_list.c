/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zone_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 12:04:00 by hmadad            #+#    #+#             */
/*   Updated: 2018/08/31 15:11:51 by hmadad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

t_base base;

void    *ft_get_free_zone(t_region *region, size_t lenWithQuantium)
{
    t_zone  *zone;

    zone = region->zone;
    while (zone)
    {
        if (zone->length >= lenWithQuantium && zone->free == TRUE)
            return (void *)zone;
        zone = zone->next;
    }
    return NULL;
}

void    *ft_create_new_zone_list(t_zone *newZone, size_t zoneLength, size_t nextZoneLength, size_t zone_header_length)
{
    t_zone  *newNext;

    if (nextZoneLength < zone_header_length)
        newNext = NULL;
    else
    {
        newNext = (void *)newZone + zone_header_length + zoneLength;
        newNext->length = nextZoneLength;
        newNext->free = TRUE;
        newNext->next = NULL;
        newNext->content = (void *)newZone + zone_header_length;
    }
    newZone->free = FALSE;
    newZone->length = zoneLength;
    newZone->next = newNext;
    newZone->content = (void *)newZone + zone_header_length;
    return (void *)newZone->content;
}