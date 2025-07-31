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

int	load_sprite_frames(t_game *game, t_sprite *sprite)
{
	char	*paths[SPRITE_FRAMES];
	int		i;
	int		width;
	int		height;

	paths[0] = "textures/test/east.xpm";
	paths[1] = "textures/test/north.xpm";
	paths[2] = "textures/test/south.xpm";
	paths[3] = "textures/test/west.xpm";
	i = 0;
	while (i < SPRITE_FRAMES)
	{
		sprite->frames[i].img = mlx_xpm_file_to_image(game->mlx, paths[i],
				&width, &height);
		sprite->frames[i].addr = mlx_get_data_addr(sprite->frames[i].img,
				&sprite->frames[i].bits_per_pixel, &sprite->frames[i].size_len,
				&sprite->frames[i].endian);
		sprite->frames[i].width = width;
		sprite->frames[i].height = height;
		i++;
	}
	sprite->current_frame = 0;
	sprite->frame_delay = 0.15;
	sprite->frame_timer = 0.0;
	return (0);
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

void	draw_sprite(t_game *game)
{
	t_sprite_calc	calc;
	int				stripe;

	calc_sprite_transform(game, &calc);
	if (calc.transform_y <= 0)
		return ;
	calc_sprite_screen_params(&calc);
	calc_draw_bounds(&calc);
	stripe = calc.draw_start_x;
	while (stripe < calc.draw_end_x)
	{
		draw_sprite_column(game, &calc, stripe);
		stripe++;
	}
}

void	get_sprite_pos(t_game *game, double *y, double *x)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->cfg->map.height)
	{
		j = 0;
		while (j < game->cfg->map.width)
		{
			if (game->cfg->map.grid[i][j] == 'C')
			{
				*y = i + 0.5;
				*x = j + 0.5;
			}
			j++;
		}
		i++;
	}
}
