/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 00:32:37 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/25 01:13:45 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	get_new_xy(int keycode, double new_xy[2], t_game *game, double speed)
{
	t_player	*p;

	p = &game->cfg->player;
	new_xy[0] = game->cfg->player.y;
	new_xy[1] = game->cfg->player.x;
	if (keycode == KEY_W)
	{
		new_xy[1] += p->dir_x * speed;
		new_xy[0] += p->dir_y * speed;
	}
	else if (keycode == KEY_S)
	{
		new_xy[1] -= p->dir_x * speed;
		new_xy[0] -= p->dir_y * speed;
	}
	else if (keycode == KEY_D)
	{
		new_xy[1] -= p->dir_y * speed;
		new_xy[0] += p->dir_x * speed;
	}
	else if (keycode == KEY_A)
	{
		new_xy[1] += p->dir_y * speed;
		new_xy[0] -= p->dir_x * speed;
	}
}

void	move_player(int keycode, t_game *game, double speed)
{
	t_player	*p;
	char		**grid;
	double		new_xy[2];

	p = &game->cfg->player;
	if (game->keys.shift == 1)
		speed *= 2;
	else if (game->keys.ctrl == 1)
		speed *= 0.5;
	get_new_xy(keycode, new_xy, game, speed);
	grid = game->cfg->map.grid;
	if (grid[(int)p->y][(int)new_xy[1]] != '1' && grid[(int)p->y][(int)new_xy[1]] != 'D')
		p->x = new_xy[1];
	if (grid[(int)new_xy[0]][(int)p->x] != '1' && grid[(int)new_xy[0]][(int)p->x] != 'D')
		p->y = new_xy[0];
}
