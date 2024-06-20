/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:10:22 by bgolding          #+#    #+#             */
/*   Updated: 2024/06/20 14:04:00 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	input_error(int argc, char *param)
{
	int	n;

	if (argc != 2)
	{
		ft_printf("Input error. Usage: ./fdf <map>.fdf\n");
		return (1);
	}
	n = ft_strlen(param);
	if (!n || n < 5)
	{
		ft_printf("Invalid map file.\n");
		return (1);
	}
	if (!ft_strnstr(&param[n - 4], ".fdf", 4))
	{
		ft_printf("Invalid map file type.\n");
		return (1);
	}
	return (0);
}

static void	load_data(t_mlx *data, char *map_name)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		clean_exit(data, EXIT_FAILURE, "malloc error (mlx_init)");
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, map_name);
	if (!data->win)
		clean_exit(data, EXIT_FAILURE, "malloc error (mlx_new_window)");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
		clean_exit(data, EXIT_FAILURE, "malloc error (mlx_new_image)");
	data->data_addr = mlx_get_data_addr(data->img, &data->bpp, \
										&data->line_len, &data->endian);
	if (!data->data_addr)
		clean_exit(data, EXIT_FAILURE, "mlx_get_data_addr error");
}

int	clean_exit(t_mlx *data, int exit_code, char *error_msg)
{
	if (data)
	{
		if (data->map)
			free_map(data->map);
		if (data->img)
			mlx_destroy_image(data->mlx, data->img);
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		free(data);
	}
	if (error_msg != NULL && errno != 0)
		perror(error_msg);
	exit(exit_code);
}

int	main(int argc, char **argv)
{
	t_mlx	*data;

	data = NULL;
	if (input_error(argc, argv[1]))
		return (1);
	data = (t_mlx *)malloc(sizeof(t_mlx));
	if (!data)
		clean_exit(data, EXIT_FAILURE, "malloc error (main)");
	load_data(data, argv[1]);
	parse_map(data, argv[1]);
	draw(data);
	hook_manager(data);
	mlx_loop(data->mlx);
	return (0);
}
