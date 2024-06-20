/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 09:50:49 by bgolding          #+#    #+#             */
/*   Updated: 2024/06/20 14:23:13 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_axis(t_point *vec, char axis)
{
	float	tmp;

	if (axis == 'y')
	{
		tmp = vec->x;
		vec->x = vec->y;
		vec->y = tmp;
	}
	else if (axis == 'z')
	{
		tmp = vec->x;
		vec->x = vec->z;
		vec->z = tmp;
	}
	return ;
}

static void	rotate_3d(t_point *point, float angle, char axis)
{
	t_point		vec;
	const float	matrix[6] = {1, 0, cos(angle), 0, sin(angle), cos(angle)};

	if (axis == 'y')
		angle *= -1;
	vec.x = point->x;
	vec.y = point->y;
	vec.z = point->z;
	set_axis(&vec, axis);
	point->x = matrix[0] * vec.x - matrix[1] * vec.y - matrix[3] * vec.z;
	point->y = matrix[1] * vec.x + matrix[2] * vec.y - matrix[4] * vec.z;
	point->z = matrix[3] * vec.x + matrix[4] * vec.y + matrix[5] * vec.z;
	set_axis(point, axis);
}

void	set_rotation(t_map *map, t_point *start, t_point *finish)
{
	if (map->rotation->z)
	{
		rotate_3d(start, map->rotation->z, 'z');
		rotate_3d(finish, map->rotation->z, 'z');
	}
	if (map->rotation->x)
	{
		rotate_3d(start, map->rotation->x, 'x');
		rotate_3d(finish, map->rotation->x, 'x');
	}
	if (map->rotation->y)
	{
		rotate_3d(start, map->rotation->y, 'y');
		rotate_3d(finish, map->rotation->y, 'y');
	}
}
