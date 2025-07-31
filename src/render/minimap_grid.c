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

void	get_minimap_color(char c, t_mini *mini, double alpha)
{
	int	color;

	color = COLOR_FLOOR;
	if (c == '1')
		color = COLOR_WALL;
	else if (c == '2' || c == 'd' || c == 'C')
		color = COLOR_GREEN;
	else if (c == 'D')
		color = COLOR_RED;
	mini->color = color;
	mini->alpha = alpha;
}

void	draw_minimap_grid(t_game *game, t_mini *mini)
{
	char	**grid;
	int		x;
	int		y;

	grid = game->cfg->map.grid;
	y = 0;
	while (y < game->cfg->map.height)
	{
		x = -1;
		while (++x < game->cfg->map.width)
		{
			if (grid[y][x] == '0' || in("NSWE", grid[y][x]))
				get_minimap_color(grid[y][x], mini, 0.6);
			else if (grid[y][x] == '1' || grid[y][x] == '2')
				get_minimap_color(grid[y][x], mini, 0.9);
			else if (grid[y][x] == 'D' || grid[y][x] == 'd')
				get_minimap_color(grid[y][x], mini, 0.9);
			else if (grid[y][x] == 'C')
				get_minimap_color(grid[y][x], mini, 0.6);
			draw_minimap_tile(game, x * mini->tile, y * mini->tile, mini);
		}
		y++;
	}
}

void	draw_minimap_tile(t_game *game, int px, int py, t_mini *mini)
{
	int	x;
	int	y;
	int	back_color;
	int	color;

	px += mini->x_offset;
	py += mini->y_offset;
	y = py;
	while (y < py + mini->tile)
	{
		x = px;
		while (x < px + mini->tile)
		{
			back_color = get_pixel(game->img, x, y);
			color = blend_colors(back_color, mini->color, mini->alpha);
			put_pixel(game->img, x, y, color);
			x++;
		}
		y++;
	}
}
