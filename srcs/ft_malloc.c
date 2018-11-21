/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 12:04:00 by hmadad            #+#    #+#             */
/*   Updated: 2018/10/31 10:58:15 by hmadad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

t_base	g_base = {.mutex = PTHREAD_MUTEX_INITIALIZER, .called = 0};

void	*ft_create_region(size_t len)
{
	void	*address;
	int		region_type;

	region_type = ft_get_type_region(len);
	address = ft_allocate_memory(len, region_type);
	if (get_list_region_length(region_type) == 0)
		address = ft_create_new_list_region(len, (t_region *)address);
	else
		address = ft_select_region(region_type, len);
	return ((void*)address);
}

void	*ft_allocate_memory(size_t len, size_t type)
{
	void	*address;
	size_t	page_size;

	page_size = getpagesize();
	if (type == TINY_TYPE)
		address = mmap(0,
				TINY_LENGTH,
				PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE,
				-1, 0);
	else if (type == SMALL_TYPE)
		address = mmap(0,
				SMALL_LENGTH,
				PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE,
				-1, 0);
	else
		address = mmap(0,
				(len + (page_size - (len % page_size))) * 100,
				PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE,
				-1, 0);
	return (address);
}

void	*malloc(size_t len)
{
	void	*address;

	pthread_mutex_lock(&g_base.mutex);
	address = NULL;
	if (!g_base.called)
	{
		g_base.called = '1';
		address = ft_create_region(len);
	}
	else
		address = ft_select_region(ft_get_type_region(len), len);
	pthread_mutex_unlock(&g_base.mutex);
	return ((void*)address);
}
