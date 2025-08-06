/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 21:50:42 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/21 21:12:32 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Sets player direction vectors and camera plane based on cardinal direction
// 1. For 'N' or 'S', sets dir_y and plane_x accordingly
// 2. For 'S', reverses dir_y and plane_x
// 3. For 'E' or 'W', sets dir_x and plane_y accordingly
// 4. For 'W', reverses dir_x and plane_y
void	set_player_direction(t_player *player, char dir)
{
	if (dir == 'N' || dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
		if (dir == 'S')
			player->dir_y *= -1;
		if (dir == 'S')
			player->plane_x *= -1;
	}
	else if (dir == 'E' || dir == 'W')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
		if (dir == 'W')
			player->dir_x *= -1;
		if (dir == 'W')
			player->plane_y *= -1;
	}
}

// Sets player position and direction
// 1. Converts int grid coordinates to double centered position
// 2. Updates player's x, y and dir fields
// 3. Calls set_player_direction to set vectors accordingly
void	set_player_position(t_player *player, int x, int y, char dir)
{
	double	f_x;
	double	f_y;

	f_x = (double) x + 0.5;
	f_y = (double) y + 0.5;
	player->x = f_x;
	player->y = f_y;
	player->dir = dir;
	set_player_direction(player, dir);
}

// Finds and sets player position and direction based on map data
// 1. Iterates over map grid rows and columns
// 2. Detects player start position marked by 'N', 'S', 'W', or 'E'
// 3. Calls set_player_position to initialize player struct
void	get_player_position(t_cfg *cfg)
{
	int	x;
	int	y;

	y = 0;
	while (y < cfg->map.height)
	{
		x = 0;
		while (x < cfg->map.width)
		{
			if (in("NSWE", cfg->map.grid[y][x]))
				set_player_position(&cfg->player, x, y, cfg->map.grid[y][x]);
			x++;
		}
		y++;
	}
}
