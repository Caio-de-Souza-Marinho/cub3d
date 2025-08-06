/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:05:17 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/24 21:56:32 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	calc_sprite_transform(t_game *g, t_sprite_calc *calc, t_sprite *s)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	sprite_x = s->x - g->cfg->player.x;
	sprite_y = s->y - g->cfg->player.y;
	calc->sprite_distance = sqrt(sprite_x * sprite_x + sprite_y * sprite_y);
	inv_det = 1.0 / (g->cfg->player.plane_x * g->cfg->player.dir_y
			- g->cfg->player.dir_x * g->cfg->player.plane_y);
	calc->transform_x = inv_det * (g->cfg->player.dir_y * sprite_x
			- g->cfg->player.dir_x * sprite_y);
	calc->transform_y = inv_det * (-g->cfg->player.plane_y * sprite_x
			+ g->cfg->player.plane_x * sprite_y);
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

void	draw_sprite_col(t_game *g, t_sprite_calc *c, int stripe, t_sprite *s)
{
	int		y;
	int		tex_x;
	int		tex_y;
	int		color;
	t_img	*sprite_img;

	sprite_img = &s->frames[s->current_frame];
	if (!sprite_img->img || !sprite_img->addr)
		return ;
	if (c->sprite_distance >= g->z_buffer[stripe])
		return ;
	tex_x = (int)(256 * (stripe - (-c->sprite_width / 2
					+ c->sprite_screen_x)) * sprite_img->width
			/ c->sprite_width) / 256;
	y = c->draw_start_y;
	while (y < c->draw_end_y)
	{
		tex_y = (((y * 256 - WIN_HEIGHT * 128 + c->sprite_height * 128)
					* sprite_img->height) / c->sprite_height) / 256;
		color = get_sprite_pixel(sprite_img, tex_x, tex_y);
		if ((color & 0x00FFFFFF) != 0)
			put_pixel(g->img, stripe, y, color);
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
