/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:34:10 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/25 01:01:09 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	handle_key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit_game(game);
	else if (keycode == KEY_W)
		game->keys.w = 1;
	else if (keycode == KEY_S)
		game->keys.s = 1;
	else if (keycode == KEY_A)
		game->keys.a = 1;
	else if (keycode == KEY_D)
		game->keys.d = 1;
	else if (keycode == KEY_LEFT)
		game->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 1;
	else if (keycode == KEY_SHIFT)
		game->keys.shift = 1;
	else if (keycode == KEY_CTRL)
		game->keys.ctrl = 1;
	else if (keycode == KEY_TAB)
		game->keys.tab = 1;
	else if (keycode == KEY_SPACE)
		handle_door(game);
	return (0);
}

int	handle_key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = 0;
	else if (keycode == KEY_S)
		game->keys.s = 0;
	else if (keycode == KEY_A)
		game->keys.a = 0;
	else if (keycode == KEY_D)
		game->keys.d = 0;
	else if (keycode == KEY_LEFT)
		game->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		game->keys.right = 0;
	else if (keycode == KEY_SHIFT)
		game->keys.shift = 0;
	else if (keycode == KEY_CTRL)
		game->keys.ctrl = 0;
	else if (keycode == KEY_TAB)
		game->keys.tab = 0;
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

int	handle_mouse_move(int x, int y, t_game *game)
{
	int		center_x;
	int		dx;
	double	sensitivity;
	int		max_dx;

	(void)y;
	center_x = WIN_WIDTH / 2;
	dx = x - center_x;
	sensitivity = 0.002;
	max_dx = 30;
	if (dx > max_dx)
		dx = max_dx;
	else if (dx < -max_dx)
		dx = -max_dx;
	if (dx < 0)
		rotate_player(KEY_LEFT, game, fabs((double)dx) * sensitivity);
	else if (dx > 0)
		rotate_player(KEY_RIGHT, game, fabs((double)dx) * sensitivity);
	return (0);
}
