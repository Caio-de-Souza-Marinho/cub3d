/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:20:29 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/18 17:22:35 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Draws a filled circle at (cx, cy) with radius r on the image.
// 1. Iterates over square bounds around circle.
// 2. For each pixel, checks if it's within circle using x² + y² <= r².
// 3. Sets pixel to COLOR_BLUE if inside the circle.
void	draw_circle(t_img *img, int cx, int cy, int r)
{
	int	x;
	int	y;

	y = -r;
	while (y <= r)
	{
		x = -r;
		while (x <= r)
		{
			if (x * x + y * y <= r * r)
				put_pixel(img, cx + x, cy + y, COLOR_BLUE);
			x++;
		}
		y++;
	}
}

// Draws a filled square centered at (cx, cy) with half-size 'size'.
// 1. Loops over a square from -size to +size.
// 2. Sets each pixel in the square to COLOR_BLUE.
void	draw_square(t_img *img, int cx, int cy, int size)
{
	int	x;
	int	y;

	y = -size;
	while (y <= size)
	{
		x = -size;
		while (x <= size)
		{
			put_pixel(img, cx + x, cy + y, COLOR_BLUE);
			x++;
		}
		y++;
	}
}

// Draws the player on the minimap.
// 1. Converts player position to screen coordinates.
// 2. Draws a circle at the position with the radius based on minimap tile size.
void	draw_minimap_player(t_game *game, t_mini *mini)
{
	int	cx;
	int	cy;

	cx = (int)(game->cfg->player.x * mini->tile) + mini->x_offset;
	cy = (int)(game->cfg->player.y * mini->tile) + mini->y_offset;
	draw_circle(game->img, cx, cy, mini->tile / 4);
}
