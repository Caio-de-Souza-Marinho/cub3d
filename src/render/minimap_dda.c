/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 21:23:24 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/26 01:16:40 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_dda_vars(t_dda *dda, t_player *p, double ray_x, double ray_y)
{
	dda->map_x = (int) p->x;
	dda->map_y = (int) p->y;
	dda->delta_dist_x = fabs(1 / ray_x);
	dda->delta_dist_y = fabs(1 / ray_y);
	dda->step_x = 0;
	dda->step_y = 0;
	dda->side_dist_x = 0;
	dda->side_dist_y = 0;
	dda->side = 0;
	dda->hit = 0;
	dda->p = p;
	dda->perp_wall_dist = 0;
}

void	setup_ray_traversal(t_dda *dda, double ray_x, double ray_y)
{
	if (ray_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (dda->p->x - dda->map_x) * dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0 - dda->p->x) * dda->delta_dist_x;
	}
	if (ray_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (dda->p->y - dda->map_y) * dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0 - dda->p->y) * dda->delta_dist_y;
	}
}

void	run_dda_loop(t_dda *dda, t_game *game)
{
	while (!dda->hit)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (game->cfg->map.grid[dda->map_y][dda->map_x] == '1')
			dda->hit = 1;
		if (game->cfg->map.grid[dda->map_y][dda->map_x] == 'D')
			dda->hit = 1;
	}
}

t_point	cast_ray_on_minimap(t_game *game, double ray_x, double ray_y)
{
	t_dda	dda;
	t_point	end;
	double	p_wall_dist;

	init_dda_vars(&dda, &game->cfg->player, ray_x, ray_y);
	setup_ray_traversal(&dda, ray_x, ray_y);
	run_dda_loop(&dda, game);
	if (dda.side == 0)
		p_wall_dist = (dda.map_x - dda.p->x + (1.0 - dda.step_x) / 2.0) / ray_x;
	else
		p_wall_dist = (dda.map_y - dda.p->y + (1.0 - dda.step_y) / 2.0) / ray_y;
	end.x = (int)((dda.p->x + ray_x * p_wall_dist) * TILE_SIZE);
	end.y = (int)((dda.p->y + ray_y * p_wall_dist) * TILE_SIZE);
	return (end);
}
