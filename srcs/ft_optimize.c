/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optimize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 17:03:27 by hmadad            #+#    #+#             */
/*   Updated: 2018/11/14 17:03:31 by hmadad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

static size_t	get_header_size(size_t region_type)
{
	if (region_type == TINY_TYPE)
		return ((sizeof(t_zone)
		+ (TINY_QUANTUM_SIZE - (sizeof(t_zone) % TINY_QUANTUM_SIZE))));
	else if (region_type == SMALL_TYPE)
		return ((sizeof(t_zone)
		+ (SMALL_QUANTUM_SIZE - (sizeof(t_zone) % SMALL_QUANTUM_SIZE))));
	else
		return ((sizeof(t_zone)
		+ (LARGE_QUANTUM_SIZE - (sizeof(t_zone) % LARGE_QUANTUM_SIZE))));
}

void			defrag(t_region *region, size_t region_type)
{
	t_zone	*current;
	t_zone	*next;
	size_t	zone_header;

	current = region->zone;
	zone_header = get_header_size(region_type);
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
