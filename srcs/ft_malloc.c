/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 12:04:00 by hmadad            #+#    #+#             */
/*   Updated: 2018/10/31 10:58:15 by hmadad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

t_base g_base;

void    *ft_create_region(size_t len)
{
    void *address;
    int regionType;

    regionType = ft_get_type_region(len);
    address = ft_allocate_memory(len, regionType);
    if (get_list_region_length(regionType) == 0)
        address = ft_create_new_list_region(len, (t_region *)address);
    else
        address = ft_select_region(regionType, len);
    return (void*)address;
}

void    *ft_allocate_memory(size_t len, size_t type)
{
    void *address;
    //size_t pageSize;

    //pageSize = getpagesize();
    if (type == TINY_TYPE)
        address = mmap(0, TINY_LENGTH, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    else if (type == SMALL_TYPE)
        address = mmap(0, SMALL_LENGTH, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    else
        address = mmap(0, (len + (PAGESIZE - (len % PAGESIZE))) * 100, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    return address;
}

void	*malloc(size_t len)
{
    void    *address;

    address = NULL;
    if (!g_base.called || g_base.called == 0)
    {
		g_base.called = 1;
        address = ft_create_region(len);
    }
    else
        address = ft_select_region(ft_get_type_region(len), len);
	return (void*)address;
}
