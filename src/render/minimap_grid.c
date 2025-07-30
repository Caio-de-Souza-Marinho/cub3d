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

int	get_door_color(char door)
{
	if (door == 'D')
		return (COLOR_RED);
	return (COLOR_GREEN);
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
				color = COLOR_FLOOR;
			else if (grid[y][x] == '1')
				color = COLOR_WALL;
			else if (grid[y][x] == '2')
				color = COLOR_GREEN;
			else if (grid[y][x] == 'D' || grid[y][x] == 'd')
				color = get_door_color(grid[y][x]);
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
