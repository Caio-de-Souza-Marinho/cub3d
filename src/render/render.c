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
	game->img->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img->img)
		return (1);
	game->img->addr = mlx_get_data_addr(game->img->img,
			&game->img->bits_per_pixel, &game->img->size_len,
			&game->img->endian);
	if (!game->img->addr)
		return (1);
	raycast_and_draw(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
	mlx_destroy_image(game->mlx, game->img->img);
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
