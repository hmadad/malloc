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

void    *ft_create_region(size_t len)
{
    void *address;
    int regionType;

    regionType = ft_get_type_region(len);
    address = ft_allocate_memory(len);
    if (get_list_region_length(regionType) == 0)
        address = ft_create_new_list_region(len, (t_region *)address);
    else
        address = ft_select_region(regionType, len);
    return (void*)address;
}

void    *ft_allocate_memory(size_t len)
{
    void *address;
    //size_t pageSize;

    //pageSize = getpagesize();
    if ((len + TINY_QUANTUM_SIZE) < TINY_LIMIT)
    {
        address = mmap(0, TINY_LENGTH, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
        printf("address => %p - %p\n", address, address + TINY_LENGTH);
        ft_putnbr_base((size_t)((address + TINY_LENGTH) - address), 10);
        write(1, "\n", 1);
    }
    else if ((len + SMALL_QUANTUM_SIZE) < SMALL_LIMIT && (len + TINY_QUANTUM_SIZE) > TINY_LIMIT)
    {
        address = mmap(0, SMALL_LENGTH, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
        printf("address => %p - %p\n", address, address + SMALL_LENGTH);
    }
    else
    {
        address = mmap(0, len + (PAGESIZE - (len % PAGESIZE)) * 100, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
        printf("address => %p - %p\n", address, address + len + (PAGESIZE - (len % PAGESIZE)) * 100);
    }

    return address;
}

void	*ft_malloc(size_t len)
{
    void    *address;

    address = NULL;
    if (!base.called || base.called == 0)
    {
        base.called = 1;
        address = ft_create_region(len);
    }
    else
        address = ft_select_region(ft_get_type_region(len), len);
    return (void*)address;
}