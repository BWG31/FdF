/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_settings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:49:30 by bgolding          #+#    #+#             */
/*   Updated: 2024/01/02 10:52:48 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_elevation(t_map *map, t_point *start, t_point *finish)
{
	start->z *= map->elevation;
	finish->z *= map->elevation;
}

void	set_zoom(t_map *map, t_point *start, t_point *finish)
{
	start->x = (start->x - map->width / 2) * map->zoom;
	start->y = (start->y - map->height / 2) * map->zoom;
	start->z *= map->zoom;
	finish->x = (finish->x - map->width / 2) * map->zoom;
	finish->y = (finish->y - map->height / 2) * map->zoom;
	finish->z *= map->zoom;
}

void	set_origin_shift(t_point *start, t_point *finish, t_map *map)
{
	start->x += map->origin->x;
	start->y += map->origin->y;
	finish->x += map->origin->x;
	finish->y += map->origin->y;
}

void	set_delta(t_delta *delta, t_point start, t_point finish)
{
	delta->x = finish.x - start.x;
	delta->y = finish.y - start.y;
	delta->max = fmax(fabs(delta->x), fabs(delta->y));
	delta->x /= delta->max;
	delta->y /= delta->max;
}
