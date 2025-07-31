/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_fov.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 20:19:16 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/26 01:40:25 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_point	ray_minimap(t_game *game, double ray_x, double ray_y, t_mini *mini);
void	draw_fov(t_game *game, t_point end, int color, t_mini *mini);

void	draw_minimap_fov(t_game *game, t_mini *mini)
{
	t_player	*p;
	t_point		end;
	t_fov		fov;
	int			i;

	i = 0;
	p = &game->cfg->player;
	while (i < NUM_RAYS)
	{
		fov.camera_x = 2.0 * i / (double)NUM_RAYS - 1.0;
		fov.ray_dir_x = p->dir_x + p->plane_x * fov.camera_x;
		fov.ray_dir_y = p->dir_y + p->plane_y * fov.camera_x;
		end = ray_minimap(game, fov.ray_dir_x, fov.ray_dir_y, mini);
		draw_fov(game, end, COLOR_RED, mini);
		i++;
	}
}
