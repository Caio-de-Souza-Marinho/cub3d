/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 14:16:54 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/19 15:01:11 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_tex	*select_texture(t_ray *ray, t_game *game);
double	calc_wall_hit_point(t_game *game, t_ray *ray);
void	draw_texture_loop(t_game *game, t_ray *ray, t_tex *tex, t_draw_args da);
double	init_tex_pos(int draw_start, int line_height, int tex_h, double *step);

// Draws the textured wall segment for a ray.
// 1. Clamps draw_start and draw_end to screen bounds.
// 2. Selects wall texture based on ray side and direction.
// 3. Calculates texture step and initial tex_pos.
// 4. Calls draw_texture_loop to draw pixels.
void	draw_texture_column(t_game *game, t_ray *ray, int x, int line_height)
{
	int		draw_start;
	int		draw_end;
	double	t_step;
	t_tex	*tex;

	draw_start = -line_height / 2 + WIN_HEIGHT / 2;
	draw_end = line_height / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	tex = select_texture(ray, game);
	draw_texture_loop(game, ray, tex, (t_draw_args){x, draw_start, draw_end,
		init_tex_pos(draw_start, line_height, tex->height, &t_step), t_step});
}

// Selects the correct wall texture for the ray.
// 1. Checks if tile is a door ('D'), returns door texture.
// 2. Uses ray side and direction to choose north/south/east/west wall texture.
t_tex	*select_texture(t_ray *ray, t_game *game)
{
	char	tile;

	tile = game->cfg->map.grid[ray->map_y][ray->map_x];
	if (tile == 'D')
		return (&game->cfg->texture.door);
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			return (&game->cfg->texture.we);
		else
			return (&game->cfg->texture.ea);
	}
	else
	{
		if (ray->dir_y < 0)
			return (&game->cfg->texture.no);
		else
			return (&game->cfg->texture.so);
	}
}

// Calculates horizontal wall hit position (used for texture X coord).
// 1. Uses player position and perpendicular wall distance.
// 2. Removes floor to get fractional wall_x (in range [0, 1]).
double	calc_wall_hit_point(t_game *game, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->cfg->player.y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = game->cfg->player.x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

// Draws wall texture to screen using vertical strip.
// 1. Calculates texture X coordinate using wall hit point.
// 2. Flips texture if necessary (based on ray direction and side).
// 3. Loops from draw_start to draw_end, calculating texture Y.
// 4. Draws each pixel from texture to screen image.
void	draw_texture_loop(t_game *game, t_ray *ray, t_tex *tex, t_draw_args da)
{
	int		y;
	int		tex_x;
	int		tex_y;
	int		color;
	double	wall_x;

	wall_x = calc_wall_hit_point(game, ray);
	tex_x = (int)(wall_x * tex->width);
	if ((ray->side == 0 && ray->dir_x < 0)
		|| (ray->side == 1 && ray->dir_y > 0))
		tex_x = tex->width - tex_x - 1;
	y = da.start;
	while (y <= da.end)
	{
		tex_y = (int)da.tex_pos;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		color = *(unsigned int *)(tex->addr + tex_y * tex->size_len
				+ tex_x * (tex->bits_per_pixel / 8));
		put_pixel(game->img, da.x, y, color);
		da.tex_pos += da.step;
		y++;
	}
}

// Initializes texture starting position and step for vertical drawing.
// 1. Calculates texture step (how much to advance in texture per screen pixel).
// 2. Calculates initial texture Y position based on draw_start and line height.
double	init_tex_pos(int draw_start, int line_height, int tex_h, double *step)
{
	*step = (double)tex_h / (double)line_height;
	return ((draw_start - (double)WIN_HEIGHT / 2
			+ (double)line_height / 2) * (*step));
}
