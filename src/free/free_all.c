/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 22:31:13 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/22 22:47:24 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_sprite(t_game *game);

void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->img)
	{
		if (game->img->img)
			mlx_destroy_image(game->mlx, game->img->img);
		free(game->img);
	}
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->cfg)
		free_config(game);
	free_sprite(game);
	if (game->z_buffer)
		free(game->z_buffer);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free(game);
}

void	free_config(t_game *game)
{
	if (!game || !game->cfg)
		return ;
	if (game->cfg->texture.no.img)
		mlx_destroy_image(game->mlx, game->cfg->texture.no.img);
	if (game->cfg->texture.so.img)
		mlx_destroy_image(game->mlx, game->cfg->texture.so.img);
	if (game->cfg->texture.we.img)
		mlx_destroy_image(game->mlx, game->cfg->texture.we.img);
	if (game->cfg->texture.ea.img)
		mlx_destroy_image(game->mlx, game->cfg->texture.ea.img);
	free(game->cfg->texture.no.path);
	free(game->cfg->texture.so.path);
	free(game->cfg->texture.we.path);
	free(game->cfg->texture.ea.path);
	if (game->cfg->map.grid)
		free_array((void **) game->cfg->map.grid);
	free(game->cfg);
}

void	free_map_copy(char **map, int height)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_sprite(t_game *game)
{
	int	i;

	i = 0;
	while (i < SPRITE_FRAMES)
	{
		if (game->sprite.frames[i].img)
			mlx_destroy_image(game->mlx, game->sprite.frames[i].img);
		i++;
	}
}
