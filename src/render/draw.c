/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 21:25:06 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/19 15:02:23 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// part 4
void	perform_dda(t_ray *ray, t_game *game)
{
	char	**grid;

	grid = game->cfg->map.grid;
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_x >= game->cfg->map.width
			|| ray->map_y < 0 || ray->map_y >= game->cfg->map.height)
			ray->hit = 1;
		else if (grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	draw_column(t_ray *ray, t_game *game, int x)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	y;

	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->cfg->player.x
				+ (1.0 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->cfg->player.y
				+ (1.0 - ray->step_y) / 2) / ray->dir_y;
	line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	draw_start = -line_height / 2 + WIN_HEIGHT / 2;
	draw_end = line_height / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	y = 0;
	while (y < draw_start)
		put_pixel(game->img, x, y++, get_rgb(game->cfg->ceiling));
	y = draw_end + 1;
	draw_texture_column(game, ray, x, line_height);
	while (y < WIN_HEIGHT)
		put_pixel(game->img, x, y++, get_rgb(game->cfg->floor));
}

int	get_rgb(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}
