/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:32:15 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/16 20:50:52 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_textures(t_cfg *cfg);

t_game	*init_game(void)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->cfg = init_config();
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	game->img = (t_img *)malloc(sizeof(t_img));
	if (!game->img)
		return (NULL);
	game->img->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img->img)
		return (NULL);
	game->img->addr = mlx_get_data_addr(game->img->img,
			&game->img->bits_per_pixel, &game->img->size_len,
			&game->img->endian);
	if (!game->img->addr)
		return (NULL);
	ft_memset(&game->keys, 0, sizeof(t_keys));
	return (game);
}

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

void	init_textures(t_cfg *cfg)
{
	cfg->texture.no.path = NULL;
	cfg->texture.so.path = NULL;
	cfg->texture.we.path = NULL;
	cfg->texture.ea.path = NULL;
	cfg->texture.no.img = NULL;
	cfg->texture.so.img = NULL;
	cfg->texture.we.img = NULL;
	cfg->texture.ea.img = NULL;
}
