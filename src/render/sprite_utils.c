/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:05:17 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/24 21:07:40 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	calc_sprite_transform(t_game *game, t_sprite_calc *calc)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	sprite_x = game->sprite.x - game->cfg->player.x;
	sprite_y = game->sprite.y - game->cfg->player.y;
	inv_det = 1.0 / (game->cfg->player.plane_x * game->cfg->player.dir_y
			- game->cfg->player.dir_x * game->cfg->player.plane_y);
	calc->transform_x = inv_det * (game->cfg->player.dir_y * sprite_x
			- game->cfg->player.dir_x * sprite_y);
	calc->transform_y = inv_det * (-game->cfg->player.plane_y * sprite_x
			+ game->cfg->player.plane_x * sprite_y);
}

void	calc_sprite_screen_params(t_sprite_calc *calc)
{
	calc->sprite_screen_x = (int)((WIN_WIDTH / 2)
			* (1 + calc->transform_x / calc->transform_y));
	calc->sprite_height = abs((int)(WIN_HEIGHT / calc->transform_y));
	calc->sprite_width = abs((int)(WIN_HEIGHT / calc->transform_y));
}

void	calc_draw_bounds(t_sprite_calc *calc)
{
	calc->draw_start_y = -calc->sprite_height / 2 + WIN_HEIGHT / 2;
	if (calc->draw_start_y < 0)
		calc->draw_start_y = 0;
	calc->draw_end_y = calc->sprite_height / 2 + WIN_HEIGHT / 2;
	if (calc->draw_end_y >= WIN_HEIGHT)
		calc->draw_end_y = WIN_HEIGHT - 1;
	calc->draw_start_x = -calc->sprite_width / 2 + calc->sprite_screen_x;
	if (calc->draw_start_x < 0)
		calc->draw_start_x = 0;
	calc->draw_end_x = calc->sprite_width / 2 + calc->sprite_screen_x;
	if (calc->draw_end_x >= WIN_WIDTH)
		calc->draw_end_x = WIN_WIDTH - 1;
}

void	draw_sprite_column(t_game *game, t_sprite_calc *calc, int stripe)
{
	int		y;
	int		tex_x;
	int		tex_y;
	int		color;
	t_img	*sprite_img;

	sprite_img = &game->sprite.frames[game->sprite.current_frame];
	if (!sprite_img->img || !sprite_img->addr)
		return ;
	if (calc->transform_y <= game->z_buffer[stripe])
		return ;
	tex_x = (int)(256 * (stripe - (-calc->sprite_width / 2
					+ calc->sprite_screen_x)) * sprite_img->width
			/ calc->sprite_width) / 256;
	y = calc->draw_start_y;
	while (y < calc->draw_end_y)
	{
		tex_y = (((y * 256 - WIN_HEIGHT * 128 + calc->sprite_height * 128)
					* sprite_img->height) / calc->sprite_height) / 256;
		color = get_sprite_pixel(sprite_img, tex_x, tex_y);
		if ((color & 0x00FFFFFF) != 0)
			put_pixel(game->img, stripe, y, color);
		y++;
	}
}

int	get_sprite_pixel(t_img *sprite_img, int tex_x, int tex_y)
{
	int	offset;

	if (tex_x < 0 || tex_x >= sprite_img->width
		|| tex_y < 0 || tex_y >= sprite_img->height)
		return (0);
	offset = tex_y * sprite_img->size_len + tex_x
		* (sprite_img->bits_per_pixel / 8);
	return (*(int *)(sprite_img->addr + offset));
}

/*
double	get_z_buffer(t_game *game, int x)
{
	if (x < 0 || x >= game->z_buffer || !game->z_buffer)
		return (1000.0);
	return (game->z_buffer[x]);
}
*/
