/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:54:18 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/26 01:41:53 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Calculates minimap tile size and offset based on screen and map size.
// 1. If not TAB mode, use fixed TILE_SIZE and no offset.
// 2. Else start with double TILE_SIZE.
// 3. Scale down if map won't fit screen (preserve aspect ration).
// 4. Center map on screen with offsets.
void	set_minimap_size(t_mini *mini, t_game *game, int tab)
{
	double	adjust;
	int		max_width;
	int		max_height;

	if (tab != 1)
	{
		mini->tile = TILE_SIZE;
		mini->x_offset = 0;
		mini->y_offset = 0;
		return ;
	}
	mini->tile = TILE_SIZE * 2;
	max_width = game->cfg->map.width * mini->tile;
	max_height = game->cfg->map.height * mini->tile;
	if (max_width >= WIN_WIDTH || max_height >= WIN_HEIGHT)
	{
		adjust = (double) WIN_WIDTH / max_width;
		if ((double) WIN_HEIGHT / max_height < adjust)
			adjust = (double) WIN_HEIGHT / max_height;
		mini->tile *= adjust;
	}
	mini->x_offset = (WIN_WIDTH - game->cfg->map.width * mini->tile) / 2;
	mini->y_offset = (WIN_HEIGHT - game->cfg->map.height * mini->tile) / 2;
}

// Draws the entire minimap on screen
// 1. Initializes minimap parameters with set_minimap_size().
// 2. Draws grid, player FOV, and player position.
void	draw_minimap(t_game *game)
{
	t_mini	mini;

	set_minimap_size(&mini, game, game->keys.tab);
	draw_minimap_grid(game, &mini);
	draw_minimap_fov(game, &mini);
	draw_minimap_player(game, &mini);
}

// Writes a pixel color into an image buffer at (x, y).
// 1. Ignore if coordinates out of screen bounds.
// 2. Calculate pixel offset and write the color.
void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->size_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// Reads a pixel color from an image buffer at (x, y).
// 1. Calculates memory offset and reads color value.
int	get_pixel(t_img *img, int x, int y)
{
	char	*pixel;
	int		color;

	pixel = img->addr + (y * img->size_len + x * (img->bits_per_pixel / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

// Blends two colors with a given alpha factor.
// 1. Performs per-channel (r, g, b) interpolation.
// 2. Returns resulting RGB color.
int	blend_colors(int base, int overlay, double a)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((overlay >> 16 & 0xFF) * a) + ((base >> 16 & 0xFF) * (1 - a)));
	g = (int)(((overlay >> 8 & 0xFF) * a) + ((base >> 8 & 0xFF) * (1 - a)));
	b = (int)(((overlay & 0xFF) * a) + ((base & 0xFF) * (1 - a)));
	return ((r << 16) | (g << 8) | b);
}
