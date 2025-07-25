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

int	can_move(int keycode, t_game *game, double speed)
{
	char	**grid;
	double	new_xy[2];

	get_new_xy(keycode, new_xy, game, speed);
	grid = game->cfg->map.grid;
	if (grid[(int)new_xy[0]][(int)new_xy[1]] == '1')
		return (0);
	if (grid[(int)new_xy[0]][(int)new_xy[1]] == 'D')
		return (0);
	return (1);
}

void	move_player(int keycode, t_game *game, double speed)
{
	t_player	*p;

	p = &game->cfg->player;
	if (!can_move(keycode, game, speed))
		return ;
	if (keycode == KEY_W)
	{
		p->x += p->dir_x * speed;
		p->y += p->dir_y * speed;
	}
	else if (keycode == KEY_S)
	{
		p->x -= p->dir_x * speed;
		p->y -= p->dir_y * speed;
	}
	else if (keycode == KEY_D)
	{
		p->x -= p->dir_y * speed;
		p->y += p->dir_x * speed;
	}
	else if (keycode == KEY_A)
	{
		p->x += p->dir_y * speed;
		p->y -= p->dir_x * speed;
	}
}
