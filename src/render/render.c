/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:33:05 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/18 14:37:57 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	player_camera_move(t_game *game);
double	get_delta_time(t_game *game);

int	render_frame(t_game *game)
{
	player_camera_move(game);
	mlx_mouse_move(game->mlx, game->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	game->mouse_x = WIN_WIDTH / 2;
	ft_memset(game->img->addr, 0, WIN_HEIGHT * game->img->size_len);
	raycast_and_draw(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
	return (0);
}

void	player_camera_move(t_game *game)
{
	double	delta;
	double	move_speed;
	double	rot_speed;

	delta = get_delta_time(game);
	move_speed = 3.0 * delta;
	rot_speed = 2.0 * delta;
	if (game->keys.w)
		move_player(KEY_W, game, move_speed);
	if (game->keys.s)
		move_player(KEY_S, game, move_speed);
	if (game->keys.a)
		move_player(KEY_A, game, move_speed);
	if (game->keys.d)
		move_player(KEY_D, game, move_speed);
	if (game->keys.left)
		rotate_player(KEY_LEFT, game, rot_speed);
	if (game->keys.right)
		rotate_player(KEY_RIGHT, game, rot_speed);
}

void	raycast_and_draw(t_game *game)
{
	int			x;
	t_ray		ray;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(&game->cfg->player, &ray, x);
		perform_dda(&ray, game);
		draw_column(&ray, game, x);
		x++;
	}
}

double	get_delta_time(t_game *game)
{
	struct timeval	current;
	double			delta;

	gettimeofday(&current, NULL);
	delta = (current.tv_sec - game->last_frame_time.tv_sec)
		+ (current.tv_usec - game->last_frame_time.tv_usec) / 1e6;
	game->last_frame_time = current;
	return (delta);
}
