/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 22:36:45 by caide-so          #+#    #+#             */
/*   Updated: 2025/07/24 21:06:24 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_one_sprite(t_game *game, t_sprite *sprite);
void	update_sprite_animation(t_sprite *sprite, double delta);

void	draw_sprite(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->sprite_count)
	{
		draw_one_sprite(game, &game->sprites[i]);
		i++;
	}
}

void	draw_one_sprite(t_game *game, t_sprite *sprite)
{
	t_sprite_calc	calc;
	int				stripe;

	calc_sprite_transform(game, &calc, sprite);
	if (calc.transform_y <= 0)
		return ;
	calc_sprite_screen_params(&calc);
	calc_draw_bounds(&calc);
	stripe = calc.draw_start_x;
	while (stripe < calc.draw_end_x)
	{
		draw_sprite_col(game, &calc, stripe, sprite);
		stripe++;
	}
}

void	update_all_sprite_animations(t_game *game, double delta)
{
	int	i;

	i = 0;
	while (i < game->sprite_count)
		update_sprite_animation(&game->sprites[i++], delta);
}

void	update_sprite_animation(t_sprite *sprite, double delta)
{
	sprite->frame_timer += delta;
	if (sprite->frame_timer >= sprite->frame_delay)
	{
		sprite->current_frame = (sprite->current_frame + 1) % SPRITE_FRAMES;
		sprite->frame_timer = 0.0;
	}
}
