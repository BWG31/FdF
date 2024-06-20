/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:55:55 by bgolding          #+#    #+#             */
/*   Updated: 2024/06/20 13:05:26 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	fdf_close_window(t_mlx *data)
{
	clean_exit(data, EXIT_SUCCESS, NULL);
	return (0);
}

static int	reset_map(t_mlx *data, int keycode)
{
	if (keycode == R_KEY)
	{
		data->map->rotation->x = asin(tan(M_PI / 6));
		data->map->rotation->y = 0;
		data->map->rotation->z = -M_PI_4;
		data->map->origin->x = WIDTH / 2;
		data->map->origin->y = HEIGHT / 2;
		if (data->map->width >= data->map->height)
			data->map->zoom = WIDTH / data->map->width / 2;
		else
			data->map->zoom = HEIGHT / data->map->height / 2;
		data->map->elevation = 0.2;
		draw(data);
		return (1);
	}
	return (0);
}

static int	side_projection(t_mlx *data, int keycode)
{
	reset_map(data, R_KEY);
	if (keycode == NUMPAD_ONE)
		*data->map->rotation = (t_rotation){M_PI_2, 0, M_PI_2};
	else if (keycode == NUMPAD_TWO)
		*data->map->rotation = (t_rotation){M_PI_2, 0, 0};
	else if (keycode == NUMPAD_THREE)
		*data->map->rotation = (t_rotation){M_PI_2, 0, -M_PI_2};
	else if (keycode == NUMPAD_FOUR)
		*data->map->rotation = (t_rotation){0, 0, 0};
	else if (keycode == NUMPAD_FIVE)
		*data->map->rotation = (t_rotation){M_PI_2, 0, M_PI};
	else if (keycode == NUMPAD_SIX)
		*data->map->rotation = (t_rotation){0, M_PI, 0};
	draw(data);
	return (1);
}

static int	fdf_key_down(int keycode, t_mlx *data)
{
	if (keycode == ESC_KEY)
		fdf_close_window(data);
	else if (keycode == MINUS_KEY || keycode == EQUAL_KEY)
		return (zoom_controls(data, keycode));
	else if (keycode == A_KEY || keycode == S_KEY || keycode == D_KEY \
			|| keycode == Q_KEY || keycode == W_KEY || keycode == E_KEY)
		return (rotate_controls(data, keycode));
	if (keycode == R_KEY)
		reset_map(data, keycode);
	if (keycode == NUMPAD_ONE || keycode == NUMPAD_TWO \
		|| keycode == NUMPAD_THREE || keycode == NUMPAD_FOUR \
		|| keycode == NUMPAD_FIVE || keycode == NUMPAD_SIX)
		return (side_projection(data, keycode));
	else if (keycode == ONE_KEY || keycode == TWO_KEY)
		return (elevation_controls(data, keycode));
	else if (keycode == UP_KEY || keycode == DOWN_KEY \
			|| keycode == LEFT_KEY || keycode == RIGHT_KEY)
		return (shift_controls(data, keycode));
	return (0);
}

void	hook_manager(t_mlx *data)
{
	mlx_hook(data->win, 2, 1L << 0, fdf_key_down, data);
	mlx_hook(data->win, 17, 0, fdf_close_window, data);
}
