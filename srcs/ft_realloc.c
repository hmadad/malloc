/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 17:13:15 by hmadad            #+#    #+#             */
/*   Updated: 2018/11/14 17:22:49 by hmadad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

t_base		g_base;

static void	ft_copy_and_free(void *new_zone,
		t_zone *old_zone, size_t new_length)
{
	size_t	i;
	char	*new_memory;
	char	*old_memory;

	i = 0;
	new_memory = (char*)new_zone;
	old_memory = (char*)old_zone->content;
	while (i < old_zone->length && i < new_length)
	{
		new_memory[i] = old_memory[i];
		i++;
	}
	old_zone->free = TRUE;
	ft_reset_str(old_zone->content);
}

static void	*ft_should_i_realloc(size_t new_length, t_zone *zone,
		t_region *region)
{
	int		type;
	size_t	len;
	void	*new_malloc;

	type = ft_get_type_region(new_length);
	if (type == TINY_TYPE)
		len = (new_length
				+ (TINY_QUANTUM_SIZE - (new_length % TINY_QUANTUM_SIZE)));
	else if (type == SMALL_TYPE)
		len = (new_length
				+ (SMALL_QUANTUM_SIZE - (new_length % SMALL_QUANTUM_SIZE)));
	else
		len = (new_length
				+ (LARGE_QUANTUM_SIZE - (new_length % LARGE_QUANTUM_SIZE)));
	if (len == zone->length)
		return (zone->content);
	else
		new_malloc = malloc(new_length);
	ft_copy_and_free(new_malloc, zone, new_length);
	region->length += zone->length;
	return (new_malloc);
}

void		*realloc(void *address, size_t new_length)
{
	t_region	*region;
	t_zone		*zone;
	void		*ptr;

	ptr = NULL;
	if (!address)
		return (malloc(new_length));
	region = ft_find_region(address);
	if (!region)
		return (NULL);
	zone = ft_find_zone(address, region);
	if (!zone)
		return (NULL);
	ptr = ft_should_i_realloc(new_length, zone, region);
	defrag(region, ft_get_type_region(zone->length));
	return (ptr);
}
