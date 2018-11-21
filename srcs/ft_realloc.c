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

	i = get_quantum(old_zone->length);
	new_memory = (char*)new_zone;
	old_memory = (char*)old_zone + i;
	i = 0;
	while (i < old_zone->length && i < new_length)
	{
		new_memory[i] = old_memory[i];
		i++;
	}
	old_zone->free = TRUE;
	ft_reset_str((void *)old_memory);
}

static void	*ft_should_i_realloc(size_t new_length, t_zone *zone)
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
		return ((void *)zone + get_quantum(new_length));
	else
	{
		pthread_mutex_unlock(&g_base.mutex);
		new_malloc = malloc(new_length);
		pthread_mutex_lock(&g_base.mutex);
	}
	ft_copy_and_free(new_malloc, zone, new_length);
	return (new_malloc);
}

void		*realloc(void *address, size_t new_length)
{
	t_region	*region;
	t_zone		*zone;
	void		*ptr;

	pthread_mutex_lock(&g_base.mutex);
	ptr = NULL;
	if (!address)
	{
		pthread_mutex_unlock(&g_base.mutex);
		return (malloc(new_length));
	}
	if (!(region = ft_find_region(address)))
	{
		pthread_mutex_unlock(&g_base.mutex);
		return (NULL);
	}
	if (!(zone = ft_find_zone(address, region)))
	{
		pthread_mutex_unlock(&g_base.mutex);
		return (NULL);
	}
	ptr = ft_should_i_realloc(new_length, zone);
	defrag(region);
	pthread_mutex_unlock(&g_base.mutex);
	return (ptr);
}
