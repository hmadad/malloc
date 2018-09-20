/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 12:04:00 by hmadad            #+#    #+#             */
/*   Updated: 2018/08/31 15:11:51 by hmadad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

t_base base;

void    *ft_search_zone(size_t len, void *address)
{
    (void)len;
    (void)address;
    return address;
}

void    *ft_create_region(size_t len)
{
    void *address;
    int regionType;
    t_region *region;

    regionType = ft_get_type_region(len);
    address = ft_allocate_memory(len);
    if (get_list_region_length(regionType) == 0)
        address = ft_create_new_list_region(len, (t_region *)address);
    else
    {
        region = ft_select_region(regionType, len);
    }
    return (void*)address;
}

void    *ft_allocate_memory(size_t len)
{
    void *address;
    //size_t pageSize;

    //pageSize = getpagesize();
    if ((len + TINY_QUANTUM_SIZE) < TINY_LIMIT)
        address = mmap(0, TINY_LENGTH, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    else if ((len + SMALL_QUANTUM_SIZE) < SMALL_LIMIT && (len + TINY_QUANTUM_SIZE) > TINY_LIMIT)
        address = mmap(0, SMALL_LENGTH, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    else
        address = mmap(0, len + (PAGESIZE - (len % PAGESIZE)) * 100, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    return address;
}

void	*ft_malloc(size_t len)
{
    void    *address;

    address = 0;
    if (!base.called || base.called == 0)
    {
        base.called = 1;
        address = ft_create_region(len);
    }
    printf("taille = %lu\n", sizeof(t_region));
    return (void*)address;
}