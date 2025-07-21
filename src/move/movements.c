/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:34:10 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/21 15:57:25 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	rotate_player(int keycode, t_game *game, double angle);
void	move_player(int keycode, t_game *game, double speed);

int	handle_key(int keycode, t_game *game)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 0.08;
	rot_speed = 0.06;
	if (keycode == KEY_ESC)
		exit_game(game);
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		rotate_player(keycode, game, rot_speed);
	else if (keycode == KEY_W || keycode == KEY_S
		|| keycode == KEY_A || keycode == KEY_D)
		move_player(keycode, game, move_speed);
	return (0);
}

void	rotate_player(int keycode, t_game *game, double angle)
{
	double	tmp_dx;
	double	tmp_px;
	double	dy;
	double	py;

	tmp_dx = game->cfg->player.dir_x;
	dy = game->cfg->player.dir_y;
	tmp_px = game->cfg->player.plane_x;
	py = game->cfg->player.plane_y;
	if (keycode == KEY_LEFT)
	{
		game->cfg->player.dir_x = tmp_dx * cos(-angle) - dy * sin(-angle);
		game->cfg->player.dir_y = tmp_dx * sin(-angle) + dy * cos(-angle);
		game->cfg->player.plane_x = tmp_px * cos(-angle) - py * sin(-angle);
		game->cfg->player.plane_y = tmp_px * sin(-angle) + py * cos(-angle);
	}
	else if (keycode == KEY_RIGHT)
	{
		game->cfg->player.dir_x = tmp_dx * cos(angle) - dy * sin(angle);
		game->cfg->player.dir_y = tmp_dx * sin(angle) + dy * cos(angle);
		game->cfg->player.plane_x = tmp_px * cos(angle) - py * sin(angle);
		game->cfg->player.plane_y = tmp_px * sin(angle) + py * cos(angle);
	}
}

void	move_player(int keycode, t_game *game, double speed)
{
	t_player	*p;

	p = &game->cfg->player;
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
