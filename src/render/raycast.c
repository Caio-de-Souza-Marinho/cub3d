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

void	init_ray(t_player *player, t_ray *ray, int x)
{
	calc_ray_dir(ray, x, player);
	calc_delta_dist(ray, player);
	calc_step_and_side_dist(ray, player);
}

// part 1
// player direction vector (default: facing north = (0, -1))
// camera plane (perpendicular to direction)
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

// part 2
void	calc_delta_dist(t_ray *ray, t_player *player)
{
	ray->map_x = (int)player->x;
	ray->map_y = (int)player->y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
}

// part 3
// calculate initial step
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
		ray->side_dist_x = (ray->map_x * 1.0 - player->x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y * 1.0 - player->y) * ray->delta_dist_y;
	}
}
