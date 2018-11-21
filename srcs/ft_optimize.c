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

void			defrag(t_region *region)
{
	t_zone	*current;
	t_zone	*next;
	size_t	zone_header;

	current = region->zone;
	zone_header = get_quantum(current->length);
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

size_t			get_quantum(size_t len)
{
	size_t	quantum;

	if (len <= (TINY_LIMIT
	+ (TINY_QUANTUM_SIZE - (TINY_LIMIT % TINY_QUANTUM_SIZE))))
		quantum = TINY_QUANTUM_SIZE;
	else if (len <= (SMALL_LIMIT
	+ (SMALL_QUANTUM_SIZE - (TINY_LIMIT % SMALL_QUANTUM_SIZE))))
		quantum = SMALL_QUANTUM_SIZE;
	else
		quantum = LARGE_QUANTUM_SIZE;
	return (sizeof(t_zone) + ((quantum - (sizeof(t_zone) % quantum))
	== quantum ? 0 : (quantum - (sizeof(t_zone) % quantum))));
}
