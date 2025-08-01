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

void	draw_minimap_player(t_game *game, t_mini *mini)
{
	int	cx;
	int	cy;

	cx = (int)(game->cfg->player.x * mini->tile) + mini->x_offset;
	cy = (int)(game->cfg->player.y * mini->tile) + mini->y_offset;
	draw_circle(game->img, cx, cy, mini->tile / 4);
}
