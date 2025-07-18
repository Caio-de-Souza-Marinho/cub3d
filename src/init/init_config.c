/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:33:19 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/18 17:09:21 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_textures(t_cfg *cfg);

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
