/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_region_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 12:04:00 by hmadad            #+#    #+#             */
/*   Updated: 2018/11/15 15:08:13 by hmadad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

t_base	g_base;

int		get_list_region_length(size_t region)
{
	t_region	*current;
	size_t		i;

	i = 0;
	current = g_base.tab_list[region - 48];
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

void	*ft_search_region_place(size_t region, size_t len)
{
	t_region	*current;
	size_t		quantum;

	current = g_base.tab_list[region - 48];
	if (region == TINY_TYPE)
		quantum = TINY_QUANTUM_SIZE;
	else if (region == SMALL_TYPE)
		quantum = SMALL_QUANTUM_SIZE;
	else
		quantum = LARGE_QUANTUM_SIZE;
	while (current)
	{
		if (ft_get_free_zone(current, (sizeof(t_zone) + (quantum
		- (sizeof(t_zone) % quantum))) + (len + (quantum - (len % quantum)))))
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	*get_last_list_region(size_t region)
{
	t_region	*current;

	current = g_base.tab_list[region - 48];
	while (current && current->next)
		current = current->next;
	return (current);
}

size_t	set_total_length(t_region *address, size_t len)
{
	size_t		quantum;
	size_t		type;

	address->next = NULL;
	type = ft_get_type_region(len);
	if (type == TINY_TYPE)
	{
		quantum = TINY_QUANTUM_SIZE;
		address->total_length = TINY_LENGTH;
	}
	else if (type == SMALL_TYPE)
	{
		quantum = SMALL_QUANTUM_SIZE;
		address->total_length = SMALL_LENGTH;
	}
	else
	{
		quantum = LARGE_QUANTUM_SIZE;
		address->total_length = (len + (PAGESIZE - (len % PAGESIZE))) * 100;
	}
	return (quantum);
}

void	*ft_create_new_list_region(size_t len, t_region *address)
{
	t_region	*last_element;
	size_t		header_len;
	size_t		zone_header;
	t_zone		*zone;
	size_t		quantum;

	quantum = set_total_length(address, len);
	header_len = (sizeof(t_region) + (quantum - (sizeof(t_region) % quantum)));
	zone_header = (sizeof(t_zone) + ((quantum - (sizeof(t_zone) % quantum))
			== quantum ? 0 : (quantum - (sizeof(t_zone) % quantum))));
	address->zone = (void *)address + header_len;
	last_element = get_last_list_region(ft_get_type_region(len));
	if (!last_element)
		g_base.tab_list[ft_get_type_region(len) - 48] = address;
	else
		last_element->next = address;
	zone = address->zone;
	zone->length = address->total_length - (header_len + zone_header
			+ (len + (quantum - (len % quantum))));
	zone->free = TRUE;
	zone->next = NULL;
	return (ft_create_new_zone_list((t_zone *)address->zone,
			(len + ((quantum - (len % quantum)) == quantum
			? 0 : (quantum - (len % quantum)))), zone_header));
}
