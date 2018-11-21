/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 12:04:00 by hmadad            #+#    #+#             */
/*   Updated: 2018/08/31 15:11:51 by hmadad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

t_base	g_base;

static void		delete_map(t_region *region, t_zone *zone)
{
	size_t		type;
	t_region	*current;
	t_region	*previous;

	type = ft_get_type_region(zone->length);
	current = g_base.tab_list[type - 48];
	previous = NULL;
	while (current)
	{
		if (current == region && g_base.tab_list[type - 48] != region)
		{
			previous->next = current->next;
			munmap(region, current->total_length);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

static size_t	is_empty_region(t_region *region)
{
	t_zone	*current;

	current = region->zone;
	while (current)
	{
		if (current->free == FALSE)
			return (FALSE);
		current = current->next;
	}
	return (TRUE);
}

void			ft_reset_str(char *str)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		str[i] = 0;
		i++;
	}
}

void			ft_prepare_reset(t_zone *zone)
{
	size_t	quantum;

	zone->free = TRUE;
	quantum = get_quantum(zone->length);
	ft_reset_str((void *)zone + quantum);
}

void			free(void *address)
{
	t_region	*region;
	t_zone		*zone;

	pthread_mutex_lock(&g_base.mutex);
	if (!address)
	{
		pthread_mutex_unlock(&g_base.mutex);
		return ;
	}
	if (!(region = ft_find_region(address)))
	{
		pthread_mutex_unlock(&g_base.mutex);
		return ;
	}
	if (!(zone = ft_find_zone(address, region)))
	{
		pthread_mutex_unlock(&g_base.mutex);
		return ;
	}
	ft_prepare_reset(zone);
	defrag(region);
	if (is_empty_region(region) == TRUE)
		delete_map(region, zone);
	pthread_mutex_unlock(&g_base.mutex);
}
