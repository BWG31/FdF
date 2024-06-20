/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:29:38 by bgolding          #+#    #+#             */
/*   Updated: 2024/06/20 13:05:53 by bgolding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include <stdio.h>

// OS specific keycodes
# ifdef __APPLE__
#  include "macos_keycodes.h"
# elif defined __linux__
#  include "linux_keycodes.h"
# else
#  error "Unsupported OS"
# endif

# define WIDTH 2400
# define HEIGHT 1500

typedef struct s_point
{
	float		x;
	float		y;
	float		z;
	int			color;
}				t_point;

typedef struct s_rotation
{
	float		x;
	float		y;
	float		z;
}				t_rotation;

typedef struct s_origin
{
	float		x;
	float		y;
}				t_origin;

typedef struct s_map
{
	t_point		**point;
	t_origin	*origin;
	t_rotation	*rotation;
	int			width;
	int			height;
	int			zoom;
	float		elevation;
}				t_map;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data_addr;
	int			bpp;
	int			line_len;
	int			endian;
	t_map		*map;
}				t_mlx;

typedef struct s_delta
{
	float		x;
	float		y;
	float		max;
}				t_delta;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_color;

// map.c
void			parse_map(t_mlx *data, char *file);
// map.utils.c
int				element_count(char const *s, int c);
void			free_map(t_map *map);
// draw.c
void			draw(t_mlx *data);
// draw_settings.c
void			set_elevation(t_map *map, t_point *start, t_point *finish);
void			set_zoom(t_map *map, t_point *start, t_point *finish);
void			set_origin_shift(t_point *start, t_point *finish, t_map *map);
void			set_delta(t_delta *delta, t_point start, t_point finish);
// draw_utils.c
void			fdf_magic_pixel(t_mlx *data, int x, int y, int color);
void			reset_img_color(t_mlx *data, int color);
int				is_on_screen(t_point point);
// rotate.c
void			set_rotation(t_map *map, t_point *start, t_point *finish);
// hooks.c
void			hook_manager(t_mlx *data);
// controls.c
int				rotate_controls(t_mlx *data, int keycode);
int				shift_controls(t_mlx *data, int keycode);
int				zoom_controls(t_mlx *data, int keycode);
int				elevation_controls(t_mlx *data, int keycode);
// main.c
int				clean_exit(t_mlx *data, int exit_code, char *error_msg);
#endif
