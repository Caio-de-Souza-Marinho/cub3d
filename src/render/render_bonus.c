/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:33:05 by caide-so          #+#    #+#             */
/*   Updated: 2025/08/05 19:04:57 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	player_camera_move(t_game *game, double delta);

// Renders a single frame of the game.
// 1. Calculates time elapsed since the last frame.
// 2. Updates player and camera movement based on input.
// 3. Updates all sprite animations.
// 4. Resets mouse position to the center of the window.
// 5. Clears the frame buffer.
// 6. Performs raycasting and draws walls.
// 7. Draws all visible sprites.
// 8. Draws the minimap.
// 9. Displays the composed frame in the game window.
int	render_frame(t_game *game)
{
	double	delta;

	delta = get_delta_time(game);
	player_camera_move(game, delta);
	update_all_sprite_animations(game, delta);
	mlx_mouse_move(game->mlx, game->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	game->mouse_x = WIN_WIDTH / 2;
	ft_memset(game->img->addr, 0, WIN_HEIGHT * game->img->size_len);
	raycast_and_draw(game);
	draw_sprite(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
	return (0);
}

// Applies movement and rotation to the player based on input.
// 1. Calculates movement and rotation speed based no frame time.
// 2. Moves the player forward or backward (W/S keys).
// 3. Strafes the player left or right (A/D keys).
// 4. Rotates the camera left or right (arrow keys).
void	player_camera_move(t_game *game, double delta)
{
	double	move_speed;
	double	rot_speed;

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

// Performs raycasting and draws vertical wall slices for the entire screen.
// 1. Loops through each vertical screen column.
// 2. Initializes the ray for current screen column.
// 3. Performs DDA to detect wall hit along the ray.
// 4. Calculates perpendicular wall distance based on hit sice.
// 5. Stores wall distance for sprite depth sorting.
// 6. Draws the vertical wall slice for the current column.
void	raycast_and_draw(t_game *game)
{
	int			x;
	t_ray		ray;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(&game->cfg->player, &ray, x);
		perform_dda(&ray, game);
		if (ray.side == 0)
			ray.perp_wall_dist = (ray.map_x - game->cfg->player.x
					+ (1.0 - ray.step_x) / 2) / ray.dir_x;
		else
			ray.perp_wall_dist = (ray.map_y - game->cfg->player.y
					+ (1.0 - ray.step_y) / 2) / ray.dir_y;
		game->z_buffer[x] = ray.perp_wall_dist;
		draw_column(&ray, game, x);
		x++;
	}
}
