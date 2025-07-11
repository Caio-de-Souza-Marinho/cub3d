/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:33:19 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/11 19:53:16 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_config	*init_config(void)
{
	t_config	*cfg;

	cfg = (t_config *) malloc(sizeof(t_config));
	cfg->ceiling.r = -1;
	cfg->ceiling.g = -1;
	cfg->ceiling.b = -1;
	cfg->floor.r = -1;
	cfg->floor.g = -1;
	cfg->floor.b = -1;
	cfg->texture.no = NULL;
	cfg->texture.so = NULL;
	cfg->texture.we = NULL;
	cfg->texture.ea = NULL;
	cfg->map.grid = NULL;
	cfg->map.height = -1;
	cfg->map.width = -1;
	cfg->player.x = -1;
	cfg->player.y = -1;
	cfg->player.dir = -1;
	return (cfg);
}
