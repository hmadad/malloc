/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                         :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 12:04:00 by hmadad            #+#    #+#             */
/*   Updated: 2018/08/31 15:11:51 by hmadad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

t_base base;

void    *ft_copy_and_free(t_zone *newZone, t_zone *oldZone)
{
    size_t i;
    char *newMemory;
    char *oldMemory;

    i = 0;
    newMemory = (char*)newZone->content;
    oldMemory = (char*)oldZone->content;
    while(i < oldZone->length && i < newZone->length)
    {
        newMemory[i] = oldMemory[i];
        i++;
    }
    oldZone->free = TRUE;
    ft_reset_str(oldZone->content);
    return newZone->content;
}

void *ft_should_i_realloc(size_t newLength, t_zone *zone)
{
    int type;
    size_t len;
    void *newMalloc;
    t_zone *newZone;

    type = ft_get_type_region(newLength);
    if (type == TINY_TYPE)
        len = (newLength + (TINY_QUANTUM_SIZE - (newLength % TINY_QUANTUM_SIZE )));
    else if (type == SMALL_TYPE)
        len = (newLength + (SMALL_QUANTUM_SIZE - (newLength % SMALL_QUANTUM_SIZE )));
    else
        len = (newLength + (LARGE_QUANTUM_SIZE - (newLength % LARGE_QUANTUM_SIZE)));
    if (len == zone->length)
        return zone;
    else
        newMalloc = ft_malloc(newLength);
    newZone = ft_find_zone(newMalloc, ft_find_region(newMalloc));

    return ft_copy_and_free(newZone, zone);
}

void	*ft_realloc(void * address, size_t newLength)
{
    t_region * region;
    t_zone * zone;

    if (!address)
        return NULL;
    region = ft_find_region(address);
    if (!region)
        return NULL;
    zone = ft_find_zone(address, region);
    if (!zone)
        return NULL;
    return ft_should_i_realloc(newLength, zone);
}