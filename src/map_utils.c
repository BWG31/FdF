/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:24:44 by bgolding          #+#    #+#             */
/*   Updated: 2024/01/03 15:26:23 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	element_count(char const *s, int c)
{
	int	count;

	count = 0;
	if (!s)
		return (0);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != '\n')
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

void	free_map(t_map *map)
{
	int	y;

	if (map)
	{
		if (map->rotation)
			free(map->rotation);
		if (map->origin)
			free(map->origin);
		y = 0;
		if (map->point)
		{
			y = 0;
			while (y < map->height)
				free(map->point[y++]);
			free(map->point);
		}
		free(map);
	}
}
