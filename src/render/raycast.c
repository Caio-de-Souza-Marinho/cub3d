/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:41:07 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/17 21:29:16 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	calc_ray_dir(t_ray *ray, int x, t_player *player);
void	calc_delta_dist(t_ray *ray, t_player *player);
void	calc_step_and_side_dist(t_ray *ray, t_player *player);

// Initializes a ray for a single screen column.
// 1. Calculates ray direction based on player and screen column.
// 2. Calculates delta distances used in DDA algorithm.
// 3. Calculates initial step direction and side distances.
void	init_ray(t_player *player, t_ray *ray, int x)
{
	calc_ray_dir(ray, x, player);
	calc_delta_dist(ray, player);
	calc_step_and_side_dist(ray, player);
}

// Calculates ray direction using player orientation and camera plane.
// 1. Gets player direction and camera plane.
// 2. Computes camera_x coordinate in range [-1, 1] across screen.
// 3. Computes final ray direction vector using player direction and camera 
// offset.
// Note: camera_x shifts from -1 (left screen) to 1 (right screen).
void	calc_ray_dir(t_ray *ray, int x, t_player *player)
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;

	dir_x = player->dir_x;
	dir_y = player->dir_y;
	plane_x = player->plane_x;
	plane_y = player->plane_y;
	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir_x = dir_x + plane_x * camera_x;
	ray->dir_y = dir_y + plane_y * camera_x;
}

// Calculates delta distances for the DDA ray traversal.
// 1. Sets the map grid position from the player's coordinates.
// 2. Calculates delta distance for x and y using ray direction.
// 3. Initializes hit flag to 0 (no wall hit yet).
void	calc_delta_dist(t_ray *ray, t_player *player)
{
	ray->map_x = (int)player->x;
	ray->map_y = (int)player->y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
}

// Calculates step direction and initial side distances for DDA.
// 1. Sets step direction along x axis (-1 or 1).
// 2. Computes initial distance from player to first x-side.
// 3. Sets step direction along y axis (-1 or 1).
// 4. Computes initial distance from player to first y-side.
void	calc_step_and_side_dist(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->y) * ray->delta_dist_y;
	}
}
