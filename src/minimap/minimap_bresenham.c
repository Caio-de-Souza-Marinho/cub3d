/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bresenham.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 00:34:45 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/26 01:42:27 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Initializes variables for Bresenham's line algorithm.
// 1. Computes dx and dy (distance in x and y).
// 2. Sets step dirextion sx and sy.
// 3. Calculates initial error term.
// 4. Returns the initialized t_bres struct
t_bres	set_vars_bres(t_point p0, t_point p1)
{
	t_bres	vars;

	vars.dx = abs(p1.x - p0.x);
	vars.dy = abs(p1.y - p0.y);
	if (p0.x < p1.x)
		vars.sx = 1;
	else
		vars.sx = -1;
	if (p0.y < p1.y)
		vars.sy = 1;
	else
		vars.sy = -1;
	vars.err = vars.dx - vars.dy;
	return (vars);
}

// Draws a line using Bresenham's algorithm, blending pixels with COLOR_FOV.
// 1. Initializes Bresenham variables.
// 2. Loops until reaching destination point p1.
// 3. Blends current pixel color with COLOR_FOV at 20% alpha.
// 4. Updates x and y coordinates based on error terms.
void	draw_bresenham_line(t_game *game, t_point p0, t_point p1, int color)
{
	t_bres	vars;
	int		b_color;

	vars = set_vars_bres(p0, p1);
	(void) color;
	while (1)
	{
		b_color = get_pixel(game->img, p0.x, p0.y);
		put_pixel(game->img, p0.x, p0.y, blend_colors(b_color, COLOR_FOV, 0.2));
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		vars.e2 = 2 * vars.err;
		if (vars.e2 > -vars.dy)
		{
			vars.err -= vars.dy;
			p0.x += vars.sx;
		}
		if (vars.e2 < vars.dx)
		{
			vars.err += vars.dx;
			p0.y += vars.sy;
		}
	}
}

// Draws the player's field of view (FOV) line on the minimap.
// 1. Adjusts end point with minimap offset.
// 2. Converts player position to screen coordinates.
// 3. Calls Bresenham line to draw from player to end.
void	draw_fov(t_game *game, t_point end, int color, t_mini *mini)
{
	t_point	p0;

	end.x += mini->x_offset;
	end.y += mini->y_offset;
	p0.x = (int)(game->cfg->player.x * mini->tile) + mini->x_offset;
	p0.y = (int)(game->cfg->player.y * mini->tile) + mini->y_offset;
	draw_bresenham_line(game, p0, end, color);
}
