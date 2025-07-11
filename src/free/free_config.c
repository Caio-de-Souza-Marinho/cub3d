/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:08:09 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/11 19:51:22 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_config(t_config *cfg)
{
	if (cfg->map.grid)
		free_array((void **) cfg->map.grid);
	if (!cfg->texture.no)
		free(cfg->texture.no);
	if (!cfg->texture.so)
		free(cfg->texture.so);
	if (!cfg->texture.we)
		free(cfg->texture.we);
	if (!cfg->texture.ea)
		free(cfg->texture.ea);
	free(cfg);
}
