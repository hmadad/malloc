/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_region_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 18:10:46 by hmadad            #+#    #+#             */
/*   Updated: 2018/11/15 11:30:48 by hmadad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

t_base		g_base;

int			ft_get_type_region(size_t len)
{
	if (len < TINY_LIMIT)
		return (TINY_TYPE);
	else if (len < SMALL_LIMIT && len >= TINY_LIMIT)
		return (SMALL_TYPE);
	else
		return (LARGE_TYPE);
}

void		*set_region_value(size_t region_type, t_region *region, size_t len)
{
	size_t		quantum;
	size_t		zone_header;
	size_t		length_with_quantum;
	void		*address;

	address = NULL;
	if (region_type == TINY_TYPE)
		quantum = TINY_QUANTUM_SIZE;
	else if (region_type == SMALL_TYPE)
		quantum = SMALL_QUANTUM_SIZE;
	else
		quantum = LARGE_QUANTUM_SIZE;
	zone_header = (sizeof(t_zone) + (quantum - (sizeof(t_zone) % quantum)));
	length_with_quantum = (len + (quantum - (len % quantum)));
	region->length = region->length - (zone_header + length_with_quantum);
	address = ft_get_free_zone(region, length_with_quantum);
	if (!address)
	{
		address = ft_allocate_memory(len, region_type);
		address = ft_create_new_list_region(len, (t_region *)address);
	}
	else
		address = ft_create_new_zone_list((t_zone *)address,
				length_with_quantum, zone_header);
	return (address);
}

void		*ft_select_region(size_t region_type, size_t len)
{
	t_region	*region;
	void		*address;

	address = NULL;
	region = ft_search_region_place(region_type, len);
	if (!region)
	{
		address = ft_allocate_memory(len, region_type);
		address = ft_create_new_list_region(len, (t_region *)address);
	}
	else
		address = set_region_value(region_type, region, len);
	return (address);
}

t_region	*ft_find_region(void *address)
{
	int			i;
	t_region	*current;

	i = 0;
	while (i < 3)
	{
		current = g_base.tab_list[i];
		while (current)
		{
			if (address > (void *)current
					&& address < ((void *)current + current->total_length))
				return (current);
			current = current->next;
		}
		i++;
	}
	return (NULL);
}
