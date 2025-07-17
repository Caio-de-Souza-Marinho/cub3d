/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:41:07 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/16 22:55:12 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_ray(t_player *player, t_ray *ray, int x);
void	put_pixel(t_img *img, int x, int y, int color);

void	raycast_and_draw(t_game *game)
{
	int			x;
	t_ray		ray;
	t_player	*player;

	player = &game->cfg->player;
	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(&game->cfg->player, &ray, x);
		//perform_dda(&ray, game);
		//draw_column(&ray, game, x);
		x++;
	}
}

void	init_ray(t_player *player, t_ray *ray, int x)
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;

	// part 1
	// player direction vector (default: facing north = (0, -1))
	dir_x = 0;
	dir_y = -1;
	// camera plane (perpendicular to direction)
	plane_x = 0.66;
	plane_y = 0.0;
	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir_x = dir_x + plane_x * camera_x;
	ray->dir_y = dir_y + plane_y * camera_x;
	// part 2
	ray->map_x = (int)player->x;
	ray->map_y = (int)player->y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	// part 3
	// part 4
	// part 5
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->size_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
