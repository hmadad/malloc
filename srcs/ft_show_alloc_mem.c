/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_alloc_mem.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 11:32:56 by hmadad            #+#    #+#             */
/*   Updated: 2018/11/15 14:01:50 by hmadad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

t_base	g_base;

static void	ft_print_free_zone(t_zone *zone, size_t quantum)
{
	write(1, "0x", 2);
	ft_putnbr_base((size_t)((void*)zone + quantum), 16);
	ft_putstr(" : ");
	ft_putnbr_base((size_t)zone->length, 10);
	ft_putstr(" octets - FREE\n");
}

void		ft_print_zone(t_zone *zone)
{
	size_t	quantum;
	size_t	total;

	total = 0;
	quantum = get_quantum(zone->length);
	while (zone)
	{
		if (zone->free == FALSE)
		{
			write(1, "0x", 2);
			ft_putnbr_base((size_t)((void*)zone + quantum), 16);
			ft_putstr(" - 0x");
			ft_putnbr_base((size_t)((void*)zone + quantum + zone->length), 16);
			ft_putstr(" : ");
			ft_putnbr_base((size_t)zone->length, 10);
			ft_putstr(" octets\n");
			total += zone->length;
		}
		else
			ft_print_free_zone(zone, quantum);
		zone = zone->next;
	}
	ft_putstr("Total : ");
	ft_putnbr_base(total, 10);
	ft_putstr(" octets\n");
}

void		ft_print_region(t_region *region, size_t region_type)
{
	while (region)
	{
		if (region_type == TINY_TYPE)
			ft_putstr("TINY : 0x");
		if (region_type == SMALL_TYPE)
			ft_putstr("SMALL : 0x");
		if (region_type == LARGE_TYPE)
			ft_putstr("LARGE : 0x");
		ft_putnbr_base((size_t)region, 16);
		write(1, "\n", 1);
		if (region->zone)
			ft_print_zone(region->zone);
		region = region->next;
	}
}

void		ft_show_alloc_mem(void)
{
	if (get_list_region_length(TINY_TYPE) != 0)
		ft_print_region(g_base.tab_list[0], TINY_TYPE);
	if (get_list_region_length(SMALL_TYPE) != 0)
		ft_print_region(g_base.tab_list[1], SMALL_TYPE);
	if (get_list_region_length(LARGE_TYPE) != 0)
		ft_print_region(g_base.tab_list[2], LARGE_TYPE);
}
