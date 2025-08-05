/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 22:26:06 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/26 01:48:02 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "macros.h"

// gettimeofday
# include <sys/time.h>

// Represents a RGB color.
// Members:
// r: Red component.
// g: Green component.
// b: Blue component.
typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}	t_color;

// Stores texture image data.
// Members:
// path: Path to the texture file.
// img: Pointer to the loaded image.
// addr: Pointer to the image pixel data.
// width: Width of the texture.
// height: Height of the texture.
// bits_per_pixel: Bits per pixel in the image.
// size_len: Size of one row of the image in bytes.
// endian: Endianness of the image data.
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

// Holds all wall and door textures.
// Members:
// no: North wall texture.
// so: South wall texture.
// we: West wall texture.
// ea: East wall texture.
// door: Door texture.
typedef struct s_texture
{
	t_tex	no;
	t_tex	so;
	t_tex	we;
	t_tex	ea;
	t_tex	door;
}	t_texture;

// Represents the map grid.
// Members:
// grid: 2D array representing the map layout.
// width: Width of the map in tiles.
// height: Height of the map in tiles.
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

// Represents the player state.
// Members:
// x: Player's X position.
// y: Player's Y position.
// dir_x: Player's direction vector (X component).
// dir_y: Player's direction vector (Y component).
// plane_x: Camera plane X component.
// plane_y: Camera plane Y component.
// dir: Carinal direction the player is facing ('N', 'S', 'E', 'W').
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

// Stores a generic image.
// Members:
// img: Pointer to the image object.
// addr: Pointer to the image pixel data.
// bits_per_pixel: Bits per pixel in the image.
// size_len: Size of one row of the image in bytes.
// endian: Endianness of the image data.
// width: Width of the image.
// height: Height of the image.
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

// Bresenham's line algorithm.
// Members:
// dx: Delta X.
// dy: Delta Y.
// sx: Step direction on X axis.
// sy: Step direction on Y axis.
// err: Current error term.
// e2: Error accumulator.
typedef struct s_bres
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
}	t_bres;

// Represents a 2D point.
// Members:
// x: X coordinate.
// y: Y coordinate.
typedef struct s_point
{
	int		x;
	int		y;
}	t_point;

// Minimap rendering properties.
// Members:
// color: Color to draw.
// alpha: Transparency factor.
// x_offset: Horizontal offset.
// y_offset: Vertical offset.
// tile: Tile size.
typedef struct s_mini
{
	int		color;
	double	alpha;
	int		x_offset;
	int		y_offset;
	int		tile;
}	t_mini;

// Holds field of view calculations.
// Members:
// camera_x: Camera X coordinate in screen space.
// ray_dir_x: Ray direction X component.
// ray_dir_y: Ray direction Y component.
typedef struct s_fov
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
}	t_fov;

// DDA (Digital Diferential Analysis) algorithm.
// Members:
// p: Pointer to the player struct.
// map_x: Current map tile X.
// map_y: Current map tile Y.
// delta_dist_x: Distance to next X side.
// delta_dist_y: Distance to next Y side.
// step_x: Step direction in X axis.
// step_y: Step direction in Y axis.
// side_dist_x: Distance from ray origin to next X side.
// side_dist_y: Distance from ray origin to next Y side.
// perp_wall_dist: Perpendicular distance to wall.
// side: Side of wall hit (0 = X, 1 = Y).
// hit: Boolean if wall was hit.
typedef struct s_dda
{
	t_player	*p;
	int			map_x;
	int			map_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	double		side_dist_x;
	double		side_dist_y;
	double		perp_wall_dist;
	int			side;
	int			hit;
}	t_dda;

// Represents a single ray's state.
// Members:
// dir_x: Ray direction X component.
// dir_y: Ray direction Y component.
// camera_x: Camera X coordinate in screen space.
// map_x: Current map tile X.
// map_y: Current map tile Y.
// side_dist_x: Distance from ray origin to next X side.
// side_dist_y: Distance from ray origin to next Y side.
// delta_dist_x: Distance to next X side.
// delta_dist_y: Distance to next Y side.
// perp_wall_dist: Perpendicular distance to wall.
// step_x: Step direction in X axis.
// step_y: Step direction in Y axis.
// hit: Boolean if wall was hit.
// side: Side of wall hit (0 = X, 1 = Y).
// wall_tex: Pointer to texture hit by ray.
// wall_x: X coordinate on the wall where ray hit.
// tex_x: X coordinate of the texture to sample.
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

// Stores keyboard input states.
// Members:
// w: W key state.
// a: A key state.
// s: S key state.
// d: D key state.
// left: left arrow key state.
// right: right arrow key state.
// shift: shift key state.
// ctrl: ctrl key state.
// tab: tab key state.
typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
	int	shift;
	int	ctrl;
	int	tab;
}	t_keys;

// Used for drawing texture columns.
// Members:
// x: X coordinate on the screen.
// start: Starting pixel to draw.
// end: Ending pixel to draw.
// tex_pos: Starting position in the texture.
// step: Step size to advance in the texture.
typedef struct s_draw_args
{
	int		x;
	int		start;
	int		end;
	double	tex_pos;
	float	step;
}	t_draw_args;

// Represents a single sprite instance.
// Members:
// x: Sprite X position.
// y: Sprite Y position.
// current_frame: Index of the current frame.
// frame_timer: Time accumulator for animation.
// frame_delay: Time between frames.
// frames: Array of sprite frames.
typedef struct s_sprite
{
	double	x;
	double	y;
	int		current_frame;
	double	frame_timer;
	double	frame_delay;
	t_img	frames[SPRITE_FRAMES];
}	t_sprite;

// Holds results of sprite projection.
// Members:
// transform_x: Transformed X coordinate (relative to camera).
// transform_y: Transformed Y coordinate (relative to camera).
// sprite_screen_x: X coordinate to draw sprite on screen.
// sprite_height: Height of the sprite on screen.
// sprite_width: Width of the sprite on the screen.
// draw_start_y: Top Y coordinate to start drawing.
// draw_start_x: Left X coordinate to stop drawing.
// draw_end_y: Bottom Y coordinate to start drawing.
// draw_end_x: Right X coordinate to stop drawing.
// sprite_distance: Distance to the sprite from player.
typedef struct s_sprite_calc
{
	double	transform_x;
	double	transform_y;
	int		sprite_screen_x;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_y;
	int		draw_start_x;
	int		draw_end_y;
	int		draw_end_x;
	double	sprite_distance;
}	t_sprite_calc;

// Holds static game configuration.
// Members:
// ceiling: Ceiling color.
// floor: Floor color.
// texture: Set of wall and door textures.
// map: Map grid data.
// player: Initial player state.
typedef struct s_cfg
{
	t_color		ceiling;
	t_color		floor;
	t_texture	texture;
	t_map		map;
	t_player	player;
}	t_cfg;

// Main struct for managing game state.
// Members:
// cfg: Pointer to configuration data.
// mlx: Pointer to MLX context.
// win: Pointer to window.
// img: Pointer to image buffer.
// keys: Keyboard state struct.
// last_frame_time: Time of last frame rendered.
// mouse_x: Mouse X position.
// mouse_y: Mouse Y position.
// sprites: Array of active sprites.
// sprite_count: Number of active sprites.
// z_buffer: Z-buffer storing wall distances.
typedef struct s_game
{
	t_cfg			*cfg;
	void			*mlx;
	void			*win;
	t_img			*img;
	t_keys			keys;
	struct timeval	last_frame_time;
	int				mouse_x;
	int				mouse_y;
	t_sprite		sprites[MAX_SPRITES];
	int				sprite_count;
	double			*z_buffer;
}	t_game;

#endif
