/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 22:26:06 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/18 20:23:09 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}	t_color;

typedef struct s_tex
{
	char	*path;
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		size_len;
	int		endian;
}	t_tex;

typedef struct s_texture
{
	t_tex	no;
	t_tex	so;
	t_tex	we;
	t_tex	ea;
}	t_texture;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	char	dir;
}	t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_len;
	int		endian;
}	t_img;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	camera_x;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	t_tex	*wall_tex;
	double	wall_x;
	int		tex_x;
}	t_ray;

typedef struct s_draw_args
{
	int		x;
	int		start;
	int		end;
	double	tex_pos;
	double	step;
}	t_draw_args;

typedef struct s_cfg
{
	t_color		ceiling;
	t_color		floor;
	t_texture	texture;
	t_map		map;
	t_player	player;
}	t_cfg;

typedef struct s_game
{
	t_cfg	*cfg;
	void	*mlx;
	void	*win;
	t_img	*img;
}	t_game;

#endif
