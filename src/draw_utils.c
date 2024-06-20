/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:44:22 by bgolding          #+#    #+#             */
/*   Updated: 2024/06/20 14:10:34 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_magic_pixel(t_mlx *data, int x, int y, int color)
{
	char	*p;

	p = data->data_addr + ((y * data->line_len) + (x * (data->bpp / 8)));
	*(unsigned int *)p = color;
}

int	is_on_screen(t_point point)
{
	if (point.x > WIDTH - 1 || point.y > HEIGHT - 1 || \
		point.x <= 0 || point.y <= 0)
		return (0);
	return (1);
}
