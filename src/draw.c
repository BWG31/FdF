/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:41:20 by bgolding          #+#    #+#             */
/*   Updated: 2024/01/03 17:27:11 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double	euclid_dist(t_point start, t_point finish)
{
	return (sqrt(pow(finish.x - start.x, 2) + pow(finish.y - start.y, 2)));
}

static int	set_color(int start_color, int finish_color, float fraction)
{
	t_color	color;

	color.r = ((start_color >> 16) & 0xFF) + fraction * \
				(((finish_color >> 16) & 0xFF) - ((start_color >> 16) & 0xFF));
	color.g = ((start_color >> 8) & 0xFF) + fraction * \
				(((finish_color >> 8) & 0xFF) - ((start_color >> 8) & 0xFF));
	color.b = (start_color & 0xFF) + fraction * \
				((finish_color & 0xFF) - (start_color & 0xFF));
	return (color.r << 16 | color.g << 8 | color.b);
}

static void	bresenham_line(t_mlx *data, t_point start, t_point finish)
{
	t_delta	delta;
	t_point	plot;
	float	dist;
	float	fraction;

	set_elevation(data->map, &start, &finish);
	set_zoom(data->map, &start, &finish);
	set_rotation(data->map, &start, &finish);
	set_origin_shift(&start, &finish, data->map);
	set_delta(&delta, start, finish);
	plot.x = start.x;
	plot.y = start.y;
	dist = euclid_dist(start, finish);
	fraction = 0;
	while (fraction <= 1)
	{
		fraction = euclid_dist(start, plot) / dist;
		plot.color = set_color(start.color, finish.color, fraction);
		if (is_on_screen(plot))
			fdf_magic_pixel(data, lrint(plot.x), lrint(plot.y), plot.color);
		plot.x += delta.x;
		plot.y += delta.y;
	}
}

void	draw(t_mlx *data)
{
	int	x;
	int	y;

	reset_img_color(data, 0x000000);
	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			if (x < data->map->width - 1)
				bresenham_line(data, data->map->point[y][x], \
									data->map->point[y][x + 1]);
			if (y < data->map->height - 1)
				bresenham_line(data, data->map->point[y][x], \
									data->map->point[y + 1][x]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
