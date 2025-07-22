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

int	render_frame(t_game *game)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 0.05;
	rot_speed = 0.05;
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
	ft_memset(game->img->addr, 0, WIN_HEIGHT * game->img->size_len);
	raycast_and_draw(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
	return (0);
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
