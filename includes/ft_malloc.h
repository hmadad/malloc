/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmadad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 12:04:00 by hmadad            #+#    #+#             */
/*   Updated: 2018/11/02 10:45:13 by hmadad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_FT_MALLOC_H
#define MALLOC_FT_MALLOC_H

#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//PAGE SIZE
#define PAGESIZE 4098
//LIMIT LENGTH
#define TINY_LIMIT 992
#define SMALL_LIMIT 127000
//REGION LENGTH
#define TINY_LENGTH 2000000
#define SMALL_LENGTH 16000000
//QUANTUM SIZE
#define TINY_QUANTUM_SIZE 16
#define SMALL_QUANTUM_SIZE 512
#define LARGE_QUANTUM_SIZE 4000

enum regionType { TINY_TYPE = 1, SMALL_TYPE = 2, LARGE_TYPE = 3};
enum boolean { FALSE = 0, TRUE = 1 };
typedef struct      s_zone {
    size_t          length;
    enum boolean    free;
    struct s_zone   *next;
    void            *content;
}                   t_zone;

typedef struct      s_region {
    enum regionType type;
    size_t          length;
    size_t          totalLength;
    struct s_region *next;
    struct s_zone   *zone;
}                   t_region;

typedef struct      s_base {
    int             called;
    struct s_region *tabList[3];
}                   t_base;

extern struct s_base base;

//MALLOC
void	    *malloc(size_t len);
void        *ft_create_region(size_t len);
void        *ft_search_zone(size_t len, void *address);
void        *ft_allocate_memory(size_t len, size_t type);

//FT_REGION_LIST
void        *ft_create_new_list_region(size_t len, t_region *address);
void        *get_last_list_region(size_t region);
int         get_list_region_length(size_t region);
void        *ft_search_region_place(size_t region, size_t len);

//FT_ZONE_LIST
void        *ft_create_new_zone_list(t_zone *newZone, size_t zoneLength, size_t zone_header_length);
void        *ft_get_free_zone(t_region *region, size_t len);
t_zone      *ft_find_zone(void *address, t_region *region);

//FT_REGION_TOOLS
void        *ft_select_region(size_t regionType, size_t lenWithQuantium);
t_region    *ft_find_region(void * address);
int         ft_get_type_region(size_t len);

//FT_SHOW_ALLOC_MEM
void        ft_show_alloc_mem();
void        ft_print_region(t_region *region, size_t regionType);
void        ft_print_zone(t_zone *zone);

//FT_PUTNBR_BASE
void        ft_putnbr_base(size_t nb, int base);

//FT_PUTSTR
void        ft_putstr(const char *str);

//FT_STRLEN
size_t      ft_strlen(const char *str);

//FREE
void	    free(void * address);
void        ft_reset_str(char *str);
void        defrag(t_region *region, size_t regionType);

//REALLOC
void	    *realloc(void * address, size_t newLength);

#endif //MALLOC_FT_MALLOC_H
