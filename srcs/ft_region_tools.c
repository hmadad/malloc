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
    else if (len < SMALL_LIMIT && len > TINY_LIMIT)
        return SMALL_TYPE;
    else
        return LARGE_TYPE;
}

void    *ft_select_region(size_t regionType, size_t len)
{
    t_region    *region;
    void        *address;

    region = ft_search_place(regionType, len);
    if (!region)
        address = ft_create_new_list_region(ft_allocate_memory(len));
    else

    return address;
}