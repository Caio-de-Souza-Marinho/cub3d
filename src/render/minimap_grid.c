/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:20:51 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/25 20:20:36 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_minimap_color(t_game *game, int x, int y, double alpha)
{
	char	c;
	int	color;
	int	back_color;

	back_color = get_pixel(game->img, x * TILE_SIZE, y * TILE_SIZE); 
	color = COLOR_FLOOR;
	c = game->cfg->map.grid[y][x];
	if (c == '1')
		color = COLOR_WALL;
	else if (c == '2' || c == 'd' || c == 'C')
		color = COLOR_GREEN;
	else if (c == 'D')
		color = COLOR_RED;
	return (blend_colors(back_color, color, alpha));
}

void	draw_minimap_grid(t_game *game)
{
	char	**grid;
	int		x;
	int		y;
	int		color;

	grid = game->cfg->map.grid;
	y = 0;
	while (y < game->cfg->map.height)
	{
		x = -1;
		while (++x < game->cfg->map.width)
		{
			if (grid[y][x] == '0' || in("NSWE", grid[y][x]))
				color = get_minimap_color(game, x, y, 0.6);
			else if (grid[y][x] == '1')
				color = get_minimap_color(game, x, y, 0.9);
			else if (grid[y][x] == '2')
				color = get_minimap_color(game, x, y, 0.9);
			else if (grid[y][x] == 'D' || grid[y][x] == 'd')
				color = get_minimap_color(game, x, y, 0.9);
			draw_minimap_tile(game, x * TILE_SIZE, y * TILE_SIZE, color);
		}
		y++;
	}
}

void	draw_minimap_tile(t_game *game, int px, int py, int color)
{
	int	x;
	int	y;

	y = py;
	while (y < py + TILE_SIZE)
	{
		x = px;
		while (x < px + TILE_SIZE)
		{
			put_pixel(game->img, x, y, color);
			x++;
		}
		y++;
	}
}
