/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:20:34 by bgolding          #+#    #+#             */
/*   Updated: 2024/01/02 10:35:41 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	rotate_controls(t_mlx *data, int keycode)
{
	if (keycode == W_KEY)
		data->map->rotation->x += M_PI / 45;
	else if (keycode == D_KEY)
		data->map->rotation->y += M_PI / 45;
	else if (keycode == E_KEY)
		data->map->rotation->z += M_PI / 45;
	else if (keycode == S_KEY)
		data->map->rotation->x -= M_PI / 45;
	else if (keycode == A_KEY)
		data->map->rotation->y -= M_PI / 45;
	else if (keycode == Q_KEY)
		data->map->rotation->z -= M_PI / 45;
	else
		return (0);
	draw(data);
	return (1);
}

int	shift_controls(t_mlx *data, int keycode)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (keycode == UP_KEY)
		y = -10;
	else if (keycode == DOWN_KEY)
		y = 10;
	else if (keycode == LEFT_KEY)
		x = -10;
	else if (keycode == RIGHT_KEY)
		x = 10;
	else
		return (0);
	data->map->origin->x += x;
	data->map->origin->y += y;
	draw(data);
	return (1);
}

int	zoom_controls(t_mlx *data, int keycode)
{
	if (keycode == MINUS_KEY && data->map->zoom > 1)
			data->map->zoom -= 1;
	else if (keycode == EQUAL_KEY)
			data->map->zoom += 1;
	else
		return (0);
	draw(data);
	return (1);
}

int	elevation_controls(t_mlx *data, int keycode)
{
	if (keycode == ONE_KEY)
		data->map->elevation -= 0.05;
	else if (keycode == TWO_KEY)
		data->map->elevation += 0.05;
	else
		return (0);
	draw(data);
	return (1);
}
