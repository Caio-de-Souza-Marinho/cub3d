/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:33:05 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/22 22:41:39 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	player_camera_move(t_game *game);

int	render_frame(t_game *game)
{
	double	delta;

	player_camera_move(game);
	delta = get_delta_time(game);
	update_sprite_animation(&game->sprite, delta);
	mlx_mouse_move(game->mlx, game->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	game->mouse_x = WIN_WIDTH / 2;
	ft_memset(game->img->addr, 0, WIN_HEIGHT * game->img->size_len);
	raycast_and_draw(game);
	draw_sprite(game);
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

	if (!game->z_buffer.buffer)
	{
		game->z_buffer.buffer = (double *)malloc(sizeof(double) * WIN_WIDTH);
		game->z_buffer.width = WIN_WIDTH;
	}
	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(&game->cfg->player, &ray, x);
		perform_dda(&ray, game);
		if (ray.side == 0)
			game->z_buffer.buffer[x] = (ray.map_x - game->cfg->player.x + 
				(1.0 - ray.step_x) / 2) / ray.dir_x;
		else
			game->z_buffer.buffer[x] = (ray.map_y - game->cfg->player.y + 
				(1.0 - ray.step_y) / 2) / ray.dir_y;
		draw_column(&ray, game, x);
		x++;
	}
}
