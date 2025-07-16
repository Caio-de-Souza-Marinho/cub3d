/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 21:50:42 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/15 22:12:06 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	set_player_position(t_player *player, int x, int y, char dir)
{
	float	f_x;
	float	f_y;

	f_x = (float) x + 0.5;
	f_y = (float) y + 0.5;
	player->x = f_x;
	player->y = f_y;
	player->dir = dir;
}

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
