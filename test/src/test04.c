/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test04.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salibert <salibert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 12:34:44 by salibert          #+#    #+#             */
/*   Updated: 2018/10/22 10:30:56 by salibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <strings.h>

#define M (1024 * 1024)

void		print(char *s)
{
	write(1, s, strlen(s));
}

int			main(void)
{
	char	*addr;

	addr = malloc(16);
	free(NULL);
	free((void *)addr + 5);
	if (realloc((void *)addr + 5, 10) == NULL)
		print("Bonjours\n");
	return (0);
}