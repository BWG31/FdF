/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:46:29 by bgolding          #+#    #+#             */
/*   Updated: 2024/01/03 15:25:15 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_map_origin_state(t_mlx *data, t_map *map)
{
	t_origin	*origin;

	if (map->width >= map->height)
		map->zoom = WIDTH / map->width / 2;
	else
		map->zoom = HEIGHT / map->height / 2;
	origin = (t_origin *)malloc(sizeof(t_origin));
	if (!origin)
		clean_exit(data, EXIT_FAILURE, "malloc error (set_map_origin_state)");
	origin->x = WIDTH / 2;
	origin->y = HEIGHT / 2;
	map->origin = origin;
	map->rotation = (t_rotation *)malloc(sizeof(t_rotation));
	if (!map->rotation)
		clean_exit(data, EXIT_FAILURE, "malloc error (set_map_origin_state)");
	map->rotation->x = asin(tan(M_PI / 6));
	map->rotation->y = 0;
	map->rotation->z = -M_PI_4;
	map->elevation = 0.2;
}

static void	set_map_dimensions(char *file, t_mlx *data)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		clean_exit(data, EXIT_FAILURE, "Could not open map file");
	line = get_next_line(fd);
	if (!line)
		clean_exit(data, EXIT_FAILURE, "Error reading map file");
	data->map->width = element_count(line, ' ');
	data->map->height = 0;
	while (line)
	{
		if (element_count(line, ' ') != data->map->width)
			clean_exit(data, EXIT_FAILURE, "Map width inconsistent");
		data->map->height += 1;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static char	**get_line_info(t_mlx *data, int fd)
{
	char	*line;
	char	*clean_line;
	char	**info;

	line = get_next_line(fd);
	if (!line)
		clean_exit(data, EXIT_FAILURE, "Error reading map (get_line_info)");
	clean_line = ft_strtrim(line, " \n");
	free(line);
	if (!clean_line)
		clean_exit(data, EXIT_FAILURE, "malloc error (ft_strtrim)");
	info = ft_split(clean_line, ' ');
	free(clean_line);
	if (!info)
		clean_exit(data, EXIT_FAILURE, "malloc error (ft_split)");
	return (info);
}

static void	read_data_to_line(t_mlx *data, int fd, t_point *point, int y)
{
	char	**info;
	int		x;
	char	*p;

	info = get_line_info(data, fd);
	x = 0;
	p = NULL;
	while (info[x])
	{
		point[x].z = (float)ft_atoi(info[x]);
		p = ft_strchr(info[x], ',');
		if (p && p[1])
			point[x].color = ft_atoi_base(++p, "0123456789ABCDEF");
		else
			point[x].color = 0xFFFFFF;
		point[x].x = (float)x;
		point[x].y = (float)y;
		free(info[x]);
		x++;
	}
	free(info[x]);
	free(info);
}

void	parse_map(t_mlx *data, char *file)
{
	int		fd;
	int		i;
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		clean_exit(data, EXIT_FAILURE, "malloc error (parse_map)");
	*map = (t_map){NULL, NULL, NULL, 0, 0, 0, 0};
	data->map = map;
	set_map_dimensions(file, data);
	set_map_origin_state(data, map);
	map->point = (t_point **)malloc(sizeof(t_point *) * (map->height));
	if (!map->point)
		clean_exit(data, EXIT_FAILURE, "malloc error (parse_map)");
	fd = open(file, O_RDONLY);
	i = 0;
	while (i < map->height)
	{
		map->point[i] = (t_point *)malloc(sizeof(t_point) * (map->width));
		if (!map->point[i])
			clean_exit(data, EXIT_FAILURE, "malloc error (parse_map)");
		read_data_to_line(data, fd, map->point[i], i);
		i++;
	}
	close (fd);
}
