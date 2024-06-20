/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:20:34 by bgolding          #+#    #+#             */
/*   Updated: 2024/06/20 15:02:46 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	rotate_controls(t_mlx *data, int keycode)
{
	static float	rotation_factor = M_PI / 45;

	if (keycode == W_KEY)
		data->map->rotation->x += rotation_factor;
	else if (keycode == D_KEY)
		data->map->rotation->y += rotation_factor;
	else if (keycode == E_KEY)
		data->map->rotation->z += rotation_factor;
	else if (keycode == S_KEY)
		data->map->rotation->x -= rotation_factor;
	else if (keycode == A_KEY)
		data->map->rotation->y -= rotation_factor;
	else if (keycode == Q_KEY)
		data->map->rotation->z -= rotation_factor;
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
	int	zoom_factor;

	zoom_factor = data->map->zoom / 10 + 1;
	if (keycode == MINUS_KEY && data->map->zoom > ZOOM_MIN)
		data->map->zoom -= zoom_factor;
	else if (keycode == EQUAL_KEY && data->map->zoom < ZOOM_MAX)
		data->map->zoom += zoom_factor;
	else
		return (0);
	printf("zoom: %d\n", data->map->zoom);
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
