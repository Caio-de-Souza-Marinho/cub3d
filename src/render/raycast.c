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
void	perform_dda(t_ray *ray, t_game *game);
void	draw_column(t_ray *ray, t_game *game, int x);
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
		perform_dda(&ray, game);
		draw_column(&ray, game, x);
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
	ray->hit = 0;
	// part 3
	// calculate initial step
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

void	perform_dda(t_ray *ray, t_game *game)
{
	char	**grid;

	// part 4
	// perform dda
	grid = game->cfg->map.grid;
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->cfg->player.x + (1.0 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->cfg->player.y + (1.0 - ray->step_y) / 2) / ray->dir_y;
}

void	draw_column(t_ray *ray, t_game *game, int x)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	y;

	line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	draw_start = -line_height / 2 + WIN_HEIGHT / 2;
	draw_end = line_height / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	y = 0;
	while (y < draw_start)
		put_pixel(game->img, x, y++, 0x222222); // Ceilling
	while (y <= draw_end)
		put_pixel(game->img, x, y++, 0xFFFFFF); // Wall
	while (y < WIN_HEIGHT)
		put_pixel(game->img, x, y++, 0x444444); // Floor
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->size_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
