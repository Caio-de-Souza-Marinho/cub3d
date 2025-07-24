/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 22:36:45 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/22 22:54:04 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_sprite_columns(t_game *game, t_sprite *sprite, int draw_start_x, 
			 int draw_end_x, int draw_start_y, int draw_end_y, 
			 int sprite_height, int sprite_width, 
			 int sprite_screen_x, double transform_y);
int	get_sprite_pixel(t_img *sprite_img, int tex_x, int tex_y);
double	get_z_buffer(t_game *game, int x);

int	load_sprite_frames(t_game *game, t_sprite *sprite)
{
	char	*paths[SPRITE_FRAMES];
	int		i;
	int		width;
	int		height;

	paths[0] = "textures/test/east.xpm";
	paths[1] = "textures/test/north.xpm";
	paths[2] = "textures/test/south.xpm";
	paths[3] = "textures/test/west.xpm";
	i = 0;
	while (i < SPRITE_FRAMES)
	{
		sprite->frames[i].img = mlx_xpm_file_to_image(game->mlx, paths[i],
					&width, &height);
		sprite->frames[i].addr = mlx_get_data_addr(sprite->frames[i].img,
			&sprite->frames[i].bits_per_pixel, &sprite->frames[i].size_len,
			&sprite->frames[i].endian);
		sprite->frames[i].width = width;
		sprite->frames[i].height = height;
		i++;
	}
	sprite->current_frame = 0;
	sprite->frame_delay = 0.15;
	sprite->frame_timer = 0.0;
	return (0);
}

void	update_sprite_animation(t_sprite *sprite, double delta)
{
	sprite->frame_timer += delta;
	if (sprite->frame_timer >= sprite->frame_delay)
	{
		sprite->current_frame = (sprite->current_frame + 1) % SPRITE_FRAMES;
		sprite->frame_timer = 0.0;
	}
}

void	draw_sprite(t_game *game)
{
	t_sprite	*sprite;
	double		sprite_x;
	double		sprite_y;
	double		inv_det;
	double		transform_x;
	double		transform_y;
	int			sprite_screen_x;
	int			sprite_height;
	int			sprite_width;
	int			draw_start_y;
	int			draw_end_y;
	int			draw_start_x;
	int			draw_end_x;

	sprite = &game->sprite;

	// Calculate sprite position relative to player
	sprite_x = sprite->x - game->cfg->player.x;
	sprite_y = sprite->y - game->cfg->player.y;

	// Transform sprite with the inverse camera matrix
	inv_det = 1.0 / (game->cfg->player.plane_x * game->cfg->player.dir_y - 
		game->cfg->player.dir_x * game->cfg->player.plane_y);

	transform_x = inv_det * (game->cfg->player.dir_y * sprite_x - 
		game->cfg->player.dir_x * sprite_y);
	transform_y = inv_det * (-game->cfg->player.plane_y * sprite_x + 
		game->cfg->player.plane_x * sprite_y);

	// Don't draw sprite if it's behind the player
	if (transform_y <= 0)
		return;

	// Calculate sprite screen position
	sprite_screen_x = (int)((WIN_WIDTH / 2) * (1 + transform_x / transform_y));

	// Calculate sprite dimensions
	sprite_height = abs((int)(WIN_HEIGHT / transform_y));
	sprite_width = abs((int)(WIN_HEIGHT / transform_y));

	// Calculate drawing bounds
	draw_start_y = -sprite_height / 2 + WIN_HEIGHT / 2;
	if (draw_start_y < 0)
		draw_start_y = 0;
	draw_end_y = sprite_height / 2 + WIN_HEIGHT / 2;
	if (draw_end_y >= WIN_HEIGHT)
		draw_end_y = WIN_HEIGHT - 1;

	draw_start_x = -sprite_width / 2 + sprite_screen_x;
	if (draw_start_x < 0)
		draw_start_x = 0;
	draw_end_x = sprite_width / 2 + sprite_screen_x;
	if (draw_end_x >= WIN_WIDTH)
		draw_end_x = WIN_WIDTH - 1;

	// Draw the sprite column by column
	draw_sprite_columns(game, sprite, draw_start_x, draw_end_x, 
		     draw_start_y, draw_end_y, sprite_height, 
		     sprite_width, sprite_screen_x, transform_y);
}

void	draw_sprite_columns(t_game *game, t_sprite *sprite, int draw_start_x, 
			 int draw_end_x, int draw_start_y, int draw_end_y, 
			 int sprite_height, int sprite_width, 
			 int sprite_screen_x, double transform_y)
{
	int		stripe;
	int		y;
	int		tex_x;
	int		tex_y;
	int		color;
	t_img	*sprite_img;

	sprite_img = &sprite->frames[sprite->current_frame];
	if (!sprite_img->img || !sprite_img->addr)
		return;

	stripe = draw_start_x;
	while (stripe < draw_end_x)
	{
		// Calculate texture x coordinate
		tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * 
			sprite_img->width / sprite_width) / 256;

		// Check if this pixel is visible (not blocked by walls)
		if (transform_y > get_z_buffer(game, stripe))
		{
			y = draw_start_y;
			while (y < draw_end_y)
			{
				// Calculate texture y coordinate
				tex_y = (((y * 256 - WIN_HEIGHT * 128 + sprite_height * 128) * 
					sprite_img->height) / sprite_height) / 256;

				// Get pixel color from sprite texture
				color = get_sprite_pixel(sprite_img, tex_x, tex_y);

				// Draw pixel if it's not transparent (assuming black is transparent)
				if ((color & 0x00FFFFFF) != 0)
					put_pixel(game->img, stripe, y, color);
				y++;
			}
		}
		stripe++;
	}
}

int	get_sprite_pixel(t_img *sprite_img, int tex_x, int tex_y)
{
	int	offset;

	// Bounds checking
	if (tex_x < 0 || tex_x >= sprite_img->width || 
		tex_y < 0 || tex_y >= sprite_img->height)
		return (0);

	offset = tex_y * sprite_img->size_len + tex_x * (sprite_img->bits_per_pixel / 8);
	return (*(int *)(sprite_img->addr + offset));
}

double	get_z_buffer(t_game *game, int x)
{
	if (x < 0 || x >= game->z_buffer.width || !game->z_buffer.buffer)
		return (1000.0);
	return (game->z_buffer.buffer[x]);
}
