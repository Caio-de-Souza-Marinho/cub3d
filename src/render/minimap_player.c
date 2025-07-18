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

void	draw_minimap_player(t_game *game)
{
	int	px;
	int	py;
	int	x;
	int	y;

	px = (int) game->cfg->player.x * 16;
	px += (game->cfg->player.x - (int) game->cfg->player.x) * 16 + 2;
	py = (int) game->cfg->player.y * 16;
	py += (game->cfg->player.y - (int) game->cfg->player.y) * 16 + 2;
	y = py - 5;
	while (y < py)
	{
		x = px - 5;
		while (x < px)
		{
			put_pixel(game->img, x, y, COLOR_BLUE);
			x++;
		}
		y++;
	}
}
