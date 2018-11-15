/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zone_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 11:47:12 by hmadad            #+#    #+#             */
/*   Updated: 2018/11/15 11:54:59 by hmadad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

t_base		g_base;

void		*ft_get_free_zone(t_region *region, size_t len_quantum)
{
	t_zone	*zone;

	zone = region->zone;
	while (zone)
	{
		if (zone->length >= len_quantum && zone->free == TRUE)
			return (void *)zone;
		zone = zone->next;
	}
	return (NULL);
}

t_zone		*ft_find_zone(void *address, t_region *region)
{
	t_zone	*current;

	current = region->zone;
	while (current)
	{
		if (current->content == address)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void		*ft_create_new_zone_list(t_zone *new_zone,
		size_t zone_length, size_t zone_header_length)
{
	t_zone	*new_next;

	new_next = NULL;
	if (new_zone->length > zone_length &&
			(new_zone->length - zone_length) > zone_header_length)
	{
		new_next = (void *)new_zone + (zone_header_length + zone_length);
		new_next->length = (new_zone->length
				- (zone_header_length + zone_length));
		new_next->free = TRUE;
		if (new_zone->next)
			new_next->next = new_zone->next;
		else
			new_next->next = NULL;
		new_next->content = (void *)new_next + zone_header_length;
	}
	new_zone->free = FALSE;
	if (new_next)
	{
		new_zone->length = zone_length;
		new_zone->next = new_next;
	}
	new_zone->content = (void *)new_zone + zone_header_length;
	return ((void *)new_zone->content);
}
