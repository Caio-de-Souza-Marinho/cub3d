/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:32:15 by caide-so          #+#    #+#             */
/*   Updated: 2025/08/01 02:01:51 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_textures(t_cfg *cfg);

// Initializes an empty game struct (t_game).
// 1. Allocates t_game.
// 2. Initializes t_cfg with init_config().
// 3. Sets mlx, win and img to NULL.
// 4. Resets keys struct to zero.
t_game	*init_empty_game(void)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->cfg = init_config();
	if (!game->cfg)
	{
		free(game);
		return (NULL);
	}
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	ft_memset(&game->keys, 0, sizeof(t_keys));
	return (game);
}

// Initializes and returns a new config struct (t_cfg).
// 1. Allocates t_cfg.
// 2. Sets ceiling and floor RGB value to -1 (unset).
// 3. Initializes texture paths and images with init_textures().
// 4. Resets map grid, height, width.
// 5. Resets player position and direction to -1 (unset).
t_cfg	*init_config(void)
{
	t_cfg	*cfg;

	cfg = (t_cfg *) malloc(sizeof(t_cfg));
	if (!cfg)
		return (NULL);
	cfg->ceiling.r = -1;
	cfg->ceiling.g = -1;
	cfg->ceiling.b = -1;
	cfg->floor.r = -1;
	cfg->floor.g = -1;
	cfg->floor.b = -1;
	init_textures(cfg);
	cfg->map.grid = NULL;
	cfg->map.height = -1;
	cfg->map.width = -1;
	cfg->player.x = -1;
	cfg->player.y = -1;
	cfg->player.dir = -1;
	return (cfg);
}

// Initializes textures paths and images to NULL.
void	init_textures(t_cfg *cfg)
{
	cfg->texture.no.path = NULL;
	cfg->texture.so.path = NULL;
	cfg->texture.we.path = NULL;
	cfg->texture.ea.path = NULL;
	cfg->texture.door.path = NULL;
	cfg->texture.no.img = NULL;
	cfg->texture.so.img = NULL;
	cfg->texture.we.img = NULL;
	cfg->texture.ea.img = NULL;
	cfg->texture.door.img = NULL;
}

// Initializes MLX graphics, window, image buffer.
// 1. Initializes mlx and creates window.
// 2. Allocates t_img and creates image with mlx_new_image().
// 3. Gets image address, sets width/height.
// 4. Allocates z_buffer for depth.
// Returns 0 on success, 1 on failure.
int	init_game_graphics(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!game->win)
		return (1);
	game->img = (t_img *)malloc(sizeof(t_img));
	if (!game->img)
		return (1);
	game->img->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img->img)
		return (1);
	game->img->addr = mlx_get_data_addr(game->img->img,
			&game->img->bits_per_pixel, &game->img->size_len,
			&game->img->endian);
	if (!game->img->addr)
		return (1);
	game->img->width = WIN_WIDTH;
	game->img->height = WIN_HEIGHT;
	game->z_buffer = (double *)malloc(sizeof(double) * WIN_WIDTH);
	return (0);
}
