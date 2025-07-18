/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 22:31:13 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/17 22:31:52 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->img)
		free(game->img);
	if (game->cfg)
		free_config(game->cfg);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free(game);
}

void	free_config(t_cfg *cfg)
{
	if (cfg->map.grid)
		free_array((void **) cfg->map.grid);
	if (cfg->texture.no.path)
		free(cfg->texture.no.path);
	if (cfg->texture.so.path)
		free(cfg->texture.so.path);
	if (cfg->texture.we.path)
		free(cfg->texture.we.path);
	if (cfg->texture.ea.path)
		free(cfg->texture.ea.path);
	if (cfg)
		free(cfg);
	cfg = NULL;
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
