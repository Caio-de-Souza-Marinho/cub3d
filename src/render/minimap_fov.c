/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_fov.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 20:19:16 by marcudos          #+#    #+#             */
/*   Updated: 2025/07/26 00:54:28 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_point	cast_ray_on_minimap(t_game *game, double ray_x, double ray_y);
void	draw_line_on_minimap(t_game *game, t_point end, int color);

void	draw_minimap_fov(t_game *game)
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
		end = cast_ray_on_minimap(game, fov.ray_dir_x, fov.ray_dir_y);
		// if ((game->keys.left || game->keys.right) && (i == 0 || i == NUM_RAYS / 2 || i == NUM_RAYS - 1))
		// {
		// 	printf(BLUE "Line Number %d\n" RESET, i);
		// 	printf(GREEN "Player Position: X = %f, y = %f\n",game->cfg->player.x,game->cfg->player.y);
		// 	printf("Player Dir: X = %f, y = %f\n" RESET,game->cfg->player.dir_x,game->cfg->player.dir_y);
		// 	printf(RED "Colision %d: X = %f, Y = %f\n" RESET, i, end.x, end.y);
		// }
		draw_line_on_minimap(game, end, COLOR_RED);
		i++;
	}
}

