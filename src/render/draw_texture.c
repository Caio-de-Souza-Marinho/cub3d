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

void	draw_texture_column(t_game *game, t_ray *ray, int x, int line_height)
{
	int	y;
	int	draw_start;
	int	draw_end;
	double	step;
	double	tex_pos;
	int	tex_x;
	int	tex_y;
	int	color;
	t_tex	*texture;

	draw_start = -line_height / 2 + WIN_HEIGHT / 2;
	draw_end = line_height / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	// 1 - Select texture (based on wall side and ray direction)
	if (ray->side == 0)
		texture = ray->dir_x < 0 ? &game->cfg->texture.we : &game->cfg->texture.ea;
	else
		texture = ray->dir_y < 0 ? &game->cfg->texture.no : &game->cfg->texture.so;
	// 2 - Calculate wall hit point (used to get tex_x)
	double	wall_x;
	if (ray->side == 0)
		wall_x = game->cfg->player.y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = game->cfg->player.x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	// 3 - Texture X coordinate
	tex_x = (int)(wall_x * (double)(texture->width));
	if ((ray->side == 0 && ray->dir_x < 0) || (ray->side == 1 && ray->dir_y > 0))
		tex_x = texture->width - tex_x - 1;
	// 4 - How much to increase tex_y per screen y
	step = 1.0 * texture->height / line_height;
	tex_pos = (draw_start - WIN_HEIGHT / 2 + line_height / 2) * step;
	// 5 - Draw
	y = draw_start;
	while (y <= draw_end)
	{
		tex_y = (int)tex_pos & (texture->height - 1);
		tex_pos += step;
		color = *(unsigned int *)(texture->addr + tex_y * texture->size_len + tex_x * (texture->bits_per_pixel / 8));
		put_pixel(game->img, x, y, color);
		y++;
	}
}

int	get_rgb(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}
